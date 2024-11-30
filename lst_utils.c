/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 23:58:07 by malde-ch          #+#    #+#             */
/*   Updated: 2024/11/30 23:31:30 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**get_command(char *cmd, char **envp)
{
	char	**command;
	char	*absolute_path;

	command = ft_split(cmd, ' ');
	absolute_path = get_absolute_path(envp, command[0]);
	if (!absolute_path)
	{
		ft_free_split(command);
		return (NULL);
	}
	free(command[0]);
	command[0] = absolute_path;
	return (command);
}

t_cmd_node	*ft_newcommand(char *cmd, char **envp)
{
	t_cmd_node	*new_lst;

	new_lst = (t_cmd_node *)malloc(sizeof(t_cmd_node));
	if (!new_lst)
		return (NULL);
	new_lst->command = get_command(cmd, envp);
	if (!new_lst->command)
	{
		free(new_lst);
		return (NULL);
	}
	new_lst->envp = envp;
	new_lst->input_fd = -1;
	new_lst->output_fd = -1;
	new_lst->pipefd[0] = -1;
	new_lst->pipefd[1] = -1;
	new_lst->next = NULL;
	return (new_lst);
}

t_cmd_node	*ft_command_add_back(t_cmd_node **lst, t_cmd_node *new)
{
	t_cmd_node	*last;

	if (!*lst)
	{
		*lst = new;
		return (*lst);
	}
	last = *lst;
	while (last->next)
		last = last->next;
	last->next = new;
	return (*lst);
}

void	ft_cmd_clear(t_cmd_node **cmd_list)
{
	t_cmd_node	*current_node;
	t_cmd_node	*next_node;

	if (!cmd_list || !*cmd_list)
		return ;
	current_node = *cmd_list;
	while (current_node)
	{
		next_node = current_node->next;
		if (current_node->command)
			ft_free_split(current_node->command);
		free(current_node);
		current_node = next_node;
	}
	*cmd_list = NULL;
}

t_cmd_node	*create_and_add_command(int argc, char **argv, char **envp)
{
	t_cmd_node	*head;
	t_cmd_node	*node;
	int			i;

	i = 2;
	head = NULL;
	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && ft_strlen(argv[1]) == 8)
	{
		handle_here_doc(argv[2]);
		i = 3;
	}
	while (i < argc - 1)
	{
		node = ft_newcommand(argv[i], envp);
		if (!node)
		{
			ft_cmd_clear(&head);
			return (NULL);
		}
		ft_command_add_back(&head, node);
		i++;
	}
	return (head);
}
