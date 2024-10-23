/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:47:31 by idomagal          #+#    #+#             */
/*   Updated: 2024/10/23 14:00:23 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_free_parms_local(char **parms)
{
	int	i;

	i = 0;
	while (parms[i] != NULL)
	{
		free(parms[i]);
		i++;
	}
	free(parms);
}

static void	ft_add_exit_code(t_minishell *shell, int status)
{
	char	*var;
	int		code;

	var = NULL;
	if (WIFEXITED(status))
	{
		code = WEXITSTATUS(status);
		var = ft_strjoin_free("?=", ft_itoa(code), 0, 1);
		ft_add_var(shell, var, 1);
		free(var);
	}
	else if (WIFSIGNALED(status))
	{
		code = 128 + WTERMSIG(status);
		var = ft_strjoin_free("?=", ft_itoa(code), 0, 1);
		ft_add_var(shell, var, 1);
		free(var);
	}
}

int	ft_exec(t_minishell *shell, char *line)
{
	pid_t	pid;
	char	**parms;
	char	*exe;
	int		status;

	parms = ft_split(line, ' ');
	exe = get_exe(parms[0], shell->env[get_path(shell->env)]);
	if (exe == NULL)
	{
		ft_free_parms_local(parms);
		ft_add_var(shell, ft_strdup("?=127"), 1);
		return (ft_error(shell, "Command not found\n", 0), EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		execve(exe, parms, shell->env);
		ft_free_parms_local(parms);
		ft_error(shell, "Execve failed\n", 0);
		ft_exit(shell, ft_strdup("126"));
	}
	waitpid(pid, &status, 0);
	ft_add_exit_code(shell, status);
	ft_free_parms_local(parms);
	return (EXIT_SUCCESS);
}
