/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:47:31 by idomagal          #+#    #+#             */
/*   Updated: 2024/09/20 15:49:29 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	ft_free_parms_local(char **parms)
{
	int	i;

	i = 0;
	while (parms[i])
		free(parms[i++]);
	free(parms);
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
		ft_add_var(shell, ft_strdup("?=127"));
		return (ft_error(shell, "Command not found\n", 0), EXIT_FAILURE);
	}
	pid = fork();
	if (pid == 0)
	{
		execve(exe, parms, shell->env);
		ft_error(shell, "Execve failed", 0);
		exit(EXIT_FAILURE);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		ft_add_var(shell, ft_strjoin_free("?=", ft_itoa(WEXITSTATUS(status)), 0, 1));
	else if (WIFSIGNALED(status))
		ft_add_var(shell, ft_strjoin_free("?=", ft_itoa(128 + WTERMSIG(status)), 0, 1));
	ft_free_parms_local(parms);
	return (EXIT_SUCCESS);
}
