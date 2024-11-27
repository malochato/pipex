/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   absolute_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: malde-ch <malo@chato.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/26 19:25:57 by malde-ch          #+#    #+#             */
/*   Updated: 2024/11/26 19:26:24 by malde-ch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

char	**get_path_dirs(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (ft_split(envp[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

char	*find_command(char **path, char *cmd)
{
	char	*absolute_path;
	char	*tmp;
	int		i;

	i = 0;
	absolute_path = NULL;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		absolute_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(absolute_path, F_OK | X_OK) == 0)
			return (absolute_path);
		free(absolute_path);
		absolute_path = NULL;
		i++;
	}
	return (NULL);
}

char	*get_absolute_path(char **envp, char *cmd)
{
	char	**path;
	char	*absolute_path;

	if (access(cmd, F_OK | X_OK) == 0)
		return (ft_strdup(cmd));
	path = get_path_dirs(envp);
	absolute_path = find_command(path, cmd);
	free_tab(path);
	return (absolute_path);
}
