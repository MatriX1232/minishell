/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 11:21:26 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/23 11:34:17 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*get_cmd(char *line)
{
	int		i;
	char	*cmd;

	i = 0;
	while (line[i] && line[i] != ' ')
		i++;
	cmd = ft_substr(line, 0, i);
	return (cmd);
}

int	get_path(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static char	*ft_return(char *exe)
{
	if (exe != NULL)
		return (exe);
	else
		return (NULL);
}

char	*get_exe(char *cmd, char *path)
{
	char	**dirs;
	char	*exe;
	char	*tmp;
	int		i;

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	dirs = ft_split(path + 5, ':');
	i = 0;
	while (dirs[i])
	{
		tmp = ft_strjoin(dirs[i++], "/");
		exe = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(exe, F_OK) == 0)
			break ;
		free(exe);
		exe = NULL;
	}
	i = 0;
	while (dirs[i])
		free(dirs[i++]);
	free(dirs);
	return (ft_return(exe));
}
