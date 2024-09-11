/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idomagal <idomagal@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:47:31 by idomagal          #+#    #+#             */
/*   Updated: 2024/09/11 13:48:29 by idomagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_exec(t_minishell *shell, char *line)
{
	pid_t	pid;
	char	**parms;
	char	*exe;

	parms = ft_split(line, ' ');
	exe = get_exe(parms[0], shell->env[get_path(shell->env)]);
	if (exe == NULL)
	{
		ft_free_parms(parms);
		return (ft_error(shell, "Command not found", 0), EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		execve(exe, parms, shell->env);
		ft_error(shell, "Execve failed", 0);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, NULL, 0);
	ft_free_parms(parms);
	return (EXIT_SUCCESS);
}

