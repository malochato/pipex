/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:48:10 by malde-ch          #+#    #+#             */
/*   Updated: 2024/11/30 23:25:10 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(const char *message, t_pipeline *pipeline)
{
	printf("acess = %d\n", access(".here_doc_tmp", F_OK));
	perror(message);
	if (access(".here_doc_tmp", F_OK) == 0)
	{
		printf("Error: here_doc\n");
		remove_file(".here_doc_tmp");
	}
	if (pipeline)
		ft_cmd_clear(&pipeline->head);
	exit(EXIT_FAILURE);
}

void	open_input_file(char *file, t_pipeline *pipeline)
{
	pipeline->input_fd = open(file, O_RDONLY, 0);
	if (pipeline->input_fd < 0)
		error_exit(file, pipeline);
}

void	open_output_file(char *file, int flags, t_pipeline *pipeline)
{
	pipeline->output_fd = open(file, flags, 0644);
	if (pipeline->output_fd < 0)
		error_exit(file, pipeline);
}

void	open_file(char *file_in, char *file_out, t_pipeline *pipeline)
{
	if (ft_strncmp(file_in, "here_doc", 8) == 0 && ft_strlen(file_in) == 8)
	{
		open_input_file(".here_doc_tmp", pipeline);
		open_output_file(file_out, O_WRONLY | O_CREAT | O_APPEND, pipeline);
	}
	else
	{
		open_input_file(file_in, pipeline);
		open_output_file(file_out, O_WRONLY | O_CREAT | O_TRUNC, pipeline);
	}
}

void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
}
