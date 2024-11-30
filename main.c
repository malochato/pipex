/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 19:41:09 by malde-ch          #+#    #+#             */
/*   Updated: 2024/11/30 08:30:01 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char **argv, char **envp)
{
	t_pipeline	pipeline;
	t_cmd_node	*head;

	if (argc <= 4)
	{
		ft_printf("Usage: ./pipex file1 cmd1 [cmd2 ... cmdN] file2\n");
		exit(EXIT_FAILURE);
	}
	head = create_and_add_command(argc, argv, envp);
	if (!head)
	{
		ft_printf("Error: command not found\n");
		exit(EXIT_FAILURE);
	}
	pipeline.head = head;
	open_file(argv[1], argv[argc - 1], &pipeline);
	create_pipeline(&pipeline);
	ft_cmd_clear(&head);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0 && ft_strlen(argv[1]) == 8)
		remove_file(".here_doc_tmp");
	return (0);
}
