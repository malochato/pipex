/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:48:10 by malde-ch          #+#    #+#             */
/*   Updated: 2024/11/16 22:10:14 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_cmd_node *get_last(t_cmd_node *head)
{
	t_cmd_node *last;

	last = head;
	while(last->next)
		last = last->next;
	return(last);
}


void	error_exit(const char *message, t_cmd_node **head)
{
	t_cmd_node *last;

	perror(message);
	if ((*head)->input_fd >= 0) 
		close((*head)->input_fd);
	last = get_last(*head);
	if (last->output_fd >= 0) 
		close(last->output_fd);
	ft_cmd_clear(head);
	exit(EXIT_FAILURE);
}


void	open_file(const char *file_in, const char *file_out, t_pipeline *pipeline )
{
	pipeline->input_fd = open(file_in, O_RDONLY, 0);
	if (pipeline->input_fd < 0)
		error_exit(file_in, -1, -1, NULL);
	pipeline->output_fd = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipeline->output_fd < 0)
		error_exit(file_out, pipeline->input_fd, -1, NULL);
}


void open_assign_file(	t_cmd_node **head, const char *file_in, const char *file_out)
{
	t_cmd_node *last;

	(*head)->input_fd = open(file_in, O_RDONLY, 0);
	if ((*head)->input_fd < 0)
		error_exit(file_in, head);
	last = get_last(*head);
	last->output_fd = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (last->output_fd < 0)
		error_exit(file_out, head);
}


