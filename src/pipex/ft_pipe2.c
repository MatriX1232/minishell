/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:09:37 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/23 16:22:39 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/structures.h"
#include "../../include/minishell.h"
#include "../../include/libraries.h"
#include "pipex.h"

int	ptr_to_idx(char *str, char *ptr)
{
	int	i;

	i = 0;
	while (i < (int)(ft_strlen(str) + 1))
	{
		if (str[i] == *ptr)
			return (i);
	}
	return (-1);
}

int	is_builtin(char *command)
{
	if (ft_strncmp(command, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(command, "echo", 5) == 0)
		return (1);
	else if (ft_strncmp(command, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(command, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(command, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(command, "pwd", 4) == 0)
		return (1);
	return (0);
}

void	execute_builtin(t_minishell *shell, char **args)
{
	if (ft_strncmp(args[0], "cd", 3) == 0)
		ft_cd(shell);
	else if (ft_strncmp(args[0], "echo", 5) == 0)
		ft_echo(shell);
	else if (ft_strncmp(args[0], "env", 4) == 0)
		ft_env(shell);
	else if (ft_strncmp(args[0], "export", 7) == 0)
		ft_export(shell);
	else if (ft_strncmp(args[0], "unset", 6) == 0)
		ft_unset(shell);
	else if (ft_strncmp(args[0], "pwd", 4) == 0)
		ft_pwd(shell);
}

int	ft_detect_pipe(t_minishell *shell)
{
	int			i;

	i = 0;
	shell->pipe.count = 0;
	while (shell->parms[i])
	{
		if (ft_strncmp(shell->parms[i], "|", 2) == 0
			|| ft_strncmp(shell->parms[i], ">", 1) == 0
			|| ft_strncmp(shell->parms[i], ">>", 2) == 0
			|| ft_strncmp(shell->parms[i], "<", 1) == 0
			|| ft_strncmp(shell->parms[i], "<<", 2) == 0)
			shell->pipe.count++;
		i++;
	}
	if (shell->pipe.count > 0)
		return (1);
	return (0);
}

int	ft_isbuiltin(char *cmd)
{
	if (ft_strncmp(cmd, "echo", 5) == 0
		|| ft_strncmp(cmd, "cd", 3) == 0
		|| ft_strncmp(cmd, "pwd", 4) == 0
		|| ft_strncmp(cmd, "export", 7) == 0
		|| ft_strncmp(cmd, "unset", 6) == 0
		|| ft_strncmp(cmd, "env", 4) == 0)
		return (1);
	return (0);
}
