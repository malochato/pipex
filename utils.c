/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:48:10 by malde-ch          #+#    #+#             */
/*   Updated: 2024/11/16 16:55:15 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	error_exit(const char *message, int infile, int outfile)
{
	perror(message);
	if (infile >= 0) 
		close(infile);
	if (outfile >= 0) 
		close(outfile);
	exit(EXIT_FAILURE);
}


void	open_file(const char *file_in, const char *file_out, t_pipeline *pipeline )
{
	pipeline->input_fd = open(file_in, O_RDONLY, 0);
	if (pipeline->input_fd < 0)
		error_exit(file_in, -1, -1);
	pipeline->output_fd = open(file_out, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (pipeline->output_fd < 0)
		error_exit(file_out, pipeline->input_fd, -1);
}