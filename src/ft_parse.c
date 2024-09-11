/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 22:07:17 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/11 15:49:05 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/structures.h"

int	ft_parse(t_minishell *shell, char *line)
{
	char	*msg;

	if (*line == '\0')
		return (EXIT_SUCCESS);
	else if (get_exe(get_cmd(line), shell->env[get_path(shell->env)]) != NULL)
		return (ft_exec(shell, line));
	else if (ft_strncmp(line, "pwd", 4) == 0)
		return (ft_pwd(shell));
	else if (ft_strncmp(line, "echo", 4) == 0)
		return (ft_echo(shell));
	else if (ft_strncmp(line, "cd", 2) == 0)
		return (ft_cd(shell));
	else if (ft_strncmp(line, "env", 4) == 0)
		return (ft_env(shell));
	else if (ft_strncmp(line, "unset", 5) == 0)
		return (ft_unset(shell));
	else if (ft_strncmp(line, "export", 6) == 0)
		return (ft_export(shell));
	else
	{
		msg = ft_strjoin("Command not found: ", line);
		return (ft_error(shell, msg, 0), ft_putchar_fd('\n', 2), free(msg), EXIT_FAILURE);
	}
}

int	check_pipe(char *line)
{
	int	i;
	int	check;

	check = 0;
	i = 0;
	while (line[i] && line[i + 1])
	{
		if (check == 0 && (line[i] == '<' || (line[i] == '<' && line[i+1] == '<')))
			check++;
		if (line[i] == '|' && check == 1)
			check++;
		if (check == 2 && (line[i] == '>' || (line[i] == '>' && line[i+1] == '>')))
		i++;
	}
	if (check == 3)
		return (1);
	return (0);
}

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

char	*get_exe(char *cmd, char *path)
{
	char	**dirs;
	char	*exe;
	char	*tmp;
	int		i;

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
	if (exe != NULL)
		return (exe);
	else
		return (NULL);
}
