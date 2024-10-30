/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 22:07:17 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/27 00:40:20 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/structures.h"

static void	ft_detected_pipes(t_minishell *shell);
static int	ft_else(t_minishell *shell, char *line);

int	ft_parse(t_minishell *shell, char *line)
{
	if (*line == '\0' || shell->parms[0] == NULL)
		return (EXIT_SUCCESS);
	else if (ft_detect_pipe(shell) == 1)
		ft_detected_pipes(shell);
	else if (ft_strncmp(shell->parms[0], "exit", 5) == 0)
		return (ft_exit(shell, line));
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
	else if (ft_check(get_exe(get_cmd(shell->parms[0]), \
		shell->env[get_path(shell->env)])) == 1)
		return (ft_exec(shell));
	else
		ft_else(shell, line);
	return (EXIT_SUCCESS);
}

static void	ft_detected_pipes(t_minishell *shell)
{
	int			i;
	int			cmd_count;
	t_Command	*commands;

	cmd_count = parse_commands(shell, shell->parms, &commands);
	execute_commands(shell, commands, cmd_count);
	i = 0;
	while (commands[i].args)
		free(commands[i++].args);
	free(commands);
}

static int	ft_else(t_minishell *shell, char *line)
{
	char	*msg;

	if (ft_add_var(shell, line, 0) == EXIT_FAILURE)
	{
		msg = ft_strjoin("Command not found: ", shell->parms[0]);
		ft_error(shell, msg, 0);
		ft_putchar_fd('\n', 2);
		ft_add_var(shell, "?=127", 1);
		free(msg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
