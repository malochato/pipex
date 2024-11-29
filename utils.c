/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:48:10 by malde-ch          #+#    #+#             */
/*   Updated: 2024/11/30 06:17:08 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(const char *message, t_pipeline *pipeline)
{
	perror(message);
	ft_cmd_clear(&pipeline->head);
	exit(EXIT_FAILURE);
}

void	open_file(char *file_in, char *file_out, t_pipeline *pipeline )
{
	pipeline->input_fd = open(file_in, O_RDONLY, 0);
	if (pipeline->input_fd < 0)
		error_exit(file_in, pipeline);
	pipeline->output_fd = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipeline->output_fd < 0)
		error_exit(file_out, pipeline);
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		//ft_printf("command: %s\n", split[i]);
		free(split[i]);
		i++;
	}
	free(split);
}
