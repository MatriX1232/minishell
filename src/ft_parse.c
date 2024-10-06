/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 22:07:17 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/25 17:52:19 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/structures.h"

int	ft_parse(t_minishell *shell, char *line)
{
	char	*msg;
	int		i;
	int		cmd_count;
	Command	*commands;

	if (*line == '\0')
		return (EXIT_SUCCESS);
	else if (ft_detect_pipe(shell) == 1)
	{
		cmd_count = parse_commands(shell, shell->parms, &commands);
		execute_commands(shell, commands, cmd_count);
		i = 0;
		while (i < cmd_count)
			free(commands[i++].args);
		free(commands);
	}
	else if (ft_strncmp(shell->parms[0], "pwd", 4) == 0)
		return (ft_pwd(shell));
	else if (ft_strncmp(shell->parms[0], "echo", 5) == 0)
		return (ft_echo(shell));
	else if (ft_strncmp(shell->parms[0], "cd", 3) == 0)
		return (ft_cd(shell));
	else if (ft_strncmp(shell->parms[0], "env", 4) == 0)
		return (ft_env(shell));
	else if (ft_strncmp(shell->parms[0], "unset", 6) == 0)
		return (ft_unset(shell));
	else if (ft_strncmp(shell->parms[0], "export", 7) == 0)
		return (ft_export(shell));
	else if (get_exe(get_cmd(shell->parms[0]), shell->env[get_path(shell->env)]) != NULL)
		return (ft_exec(shell, line));
	else
	{
		if (ft_add_var(shell, line) == EXIT_FAILURE)
			return (msg = ft_strjoin("Command not found: ", shell->parms[0]), ft_error(\
			shell, msg, 0), ft_putchar_fd('\n', 2), free(msg), EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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
