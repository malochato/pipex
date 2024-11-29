/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:46:01 by malde-ch          #+#    #+#             */
/*   Updated: 2024/11/30 06:22:49 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	*execute_command(t_cmd_node *node)
{
	ft_printf("command: %s\n", node->command[0]);
	ft_printf("command: %s\n", node->command[1]);

	
	if (dup2(node->input_fd, STDIN_FILENO) == -1)
		return ("dup2 input");
	close(node->input_fd);
	if (node->next != NULL)
	{
		close(node->pipefd[0]);
		if (dup2(node->pipefd[1], STDOUT_FILENO) == -1)
			return ("dup2 pipe");
		close(node->pipefd[1]);
	}
	else if (node->next == NULL)
	{
		if (dup2(node->output_fd, STDOUT_FILENO) == -1)
			return ("dup2 output");
		close(node->output_fd);
	}
	execve(node->command[0], node->command, node->envp);
	return ("execve");
}

static void	update_input_fd(int pipefd[2], t_cmd_node *current)
{
	if (current->input_fd != -1)
		close(current->input_fd);
	if (current->next != NULL)
	{
		close(pipefd[1]);
		current->next->input_fd = pipefd[0];
	}
}

char	*handle_command_node(t_cmd_node *current)
{
	int		pipefd[2];
	pid_t	pid;

	if (current->next != NULL && pipe(pipefd) == -1)
		return ("pipe");
	pid = fork();
	if (pid == -1)
		return ("fork");
	if (pid == 0)
	{
		if (current->next != NULL)
			current->pipefd[1] = pipefd[1];
		return (execute_command(current));
	}
	else
	{
		wait(&pid);
		update_input_fd(pipefd, current);
	}
	return (NULL);
}

void	create_pipeline(t_pipeline *pipeline)
{
	t_cmd_node	*current;
	char		*error;

	current = pipeline->head;
	current->input_fd = pipeline->input_fd;
	while (current != NULL)
	{
		if (current->next == NULL)
			current->output_fd = pipeline->output_fd;
		error = handle_command_node(current);
		if (error)
			error_exit(error, pipeline);
		current = current->next;
	}
}
