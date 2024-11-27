/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:46:01 by malde-ch          #+#    #+#             */
/*   Updated: 2024/11/26 20:01:34 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	execute_command(t_cmd_node *node)
{
	if (dup2(node->input_fd, STDIN_FILENO) == -1)
		error_exit("dup2 input", node->input_fd, node->output_fd);
	close(node->input_fd);
	if (node->next != NULL)
	{
		close(node->pipefd[0]);
		if (dup2(node->pipefd[1], STDOUT_FILENO) == -1)
			error_exit("dup2 pipe", node->input_fd, node->output_fd);
		close(node->pipefd[1]);
	}
	else if (node->next == NULL)
	{
		if (dup2(node->output_fd, STDOUT_FILENO) == -1)
			error_exit("dup2 output", -1, node->output_fd);
		close(node->output_fd);
	}
	execve(node->command[0], node->command, node->envp);
	error_exit("execve", -1, -1);
}

static void	update_input_fd(int *input_fd, int pipefd[2], t_cmd_node *current)
{
	if (*input_fd != -1)
		close(*input_fd);
	if (current->next != NULL)
	{
		close(pipefd[1]);
		*input_fd = pipefd[0];
	}
}

void	handle_command_node(t_cmd_node *current, int *input_fd, int output_fd)
{
	int		pipefd[2];
	pid_t	pid;

	if (current->next != NULL && pipe(pipefd) == -1)
		error_exit("pipe", *input_fd, output_fd);
	pid = fork();
	if (pid == -1)
		error_exit("fork", *input_fd, output_fd);
	if (pid == 0)
	{
		if (current->next != NULL)
		{
			current->pipefd[0] = pipefd[0];
			current->pipefd[1] = pipefd[1];
		}
		execute_command(current);
	}
	else
	{
		update_input_fd(input_fd, pipefd, current);
	}
	wait(&pid);
}

void	create_pipeline(t_pipeline *pipeline)
{
	t_cmd_node	*current;
	int			input_fd;

	current = pipeline->head;
	input_fd = pipeline->input_fd;
	while (current != NULL)
	{
		current->input_fd = input_fd;
		if (current->next == NULL)
			current->output_fd = pipeline->output_fd;
		handle_command_node(current, &input_fd, pipeline->output_fd);
		current = current->next;
	}
}
