/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/13 20:39:12 by malde-ch          #+#    #+#             */
/*   Updated: 2024/11/16 16:37:53 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "libft/libft.h"

# include <sys/wait.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>



# include <stdio.h>


typedef struct s_command_node {
	char **command;
	char **envp;
	int input_fd;
	int output_fd;
	int pipefd[2];
	struct s_command_node *next;
} t_cmd_node;

typedef struct s_pipeline {
	int input_fd;
	int output_fd;
	t_cmd_node *head;
} t_pipeline;

void	error_exit(const char *message, int infile, int outfile);
void	open_file(const char *file_in, const char *file_out, t_pipeline *pipeline );

void	create_pipeline(t_pipeline *pipeline);

char *get_absolute_path(char **envp, char *cmd);


t_cmd_node	*ft_newcommand(char *cmd, char **envp);
t_cmd_node *ft_command_add_back(t_cmd_node **lst, t_cmd_node *new);
void	ft_cmd_clear(t_cmd_node **lst);
t_cmd_node *create_and_add_command(int argc, char **argv, char **envp);



#endif