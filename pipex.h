/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:39:12 by malde-ch          #+#    #+#             */
/*   Updated: 2024/11/30 08:26:50 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "libft/libft.h"

# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

typedef struct s_cmd_node
{
	char				**command;
	char				**envp;
	int					input_fd;
	int					output_fd;
	int					pipefd[2];
	struct s_cmd_node	*next;
}	t_cmd_node;

typedef struct s_pipeline
{
	int			input_fd;
	int			output_fd;
	t_cmd_node	*head;
}	t_pipeline;

void		error_exit(const char *message, t_pipeline *pipeline);
void		open_file(char *file_in, char *file_out, t_pipeline *pipeline );
void		ft_free_split(char **split);

void		create_pipeline(t_pipeline *pipeline);

char		*get_absolute_path(char **envp, char *cmd);

t_cmd_node	*ft_newcommand(char *cmd, char **envp);
t_cmd_node	*ft_command_add_back(t_cmd_node **lst, t_cmd_node *new);
void		ft_cmd_clear(t_cmd_node **lst);
t_cmd_node	*create_and_add_command(int argc, char **argv, char **envp);

void		handle_here_doc(char *delimiter);


void		remove_file(const char *filename);



#endif