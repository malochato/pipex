/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:45:20 by malde-ch          #+#    #+#             */
/*   Updated: 2024/11/30 23:30:33 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	handle_here_doc(char *delimiter)
{
	char	*line;
	int		fd;

	fd = open(".here_doc_tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd < 0)
		error_exit("Error opening temporary file", NULL);
	while (1)
	{
		ft_printf("heredoc> ");
		line = get_next_line(STDIN_FILENO);
		if (!line || (ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0 \
					&& ft_strlen(line) - 1 == ft_strlen(delimiter)))
		{
			free(line);
			break ;
		}
		write(fd, line, ft_strlen(line));
		write(fd, "\n", 1);
		free(line);
	}
	close(fd);
}

void	remove_file(const char *filename)
{
	if (unlink(filename) == -1)
		error_exit("Error removing temporary file", NULL);
}
