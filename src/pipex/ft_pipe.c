/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:29:48 by idomagal          #+#    #+#             */
/*   Updated: 2024/10/23 18:12:57 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/libraries.h"
#include "../../include/structures.h"
#include "pipex.h"

void	ft_init_vars(t_vars *vars)
{
	vars->cmd_count = 0;
	vars->cmds_size = 10;
	vars->idx = 0;
	vars->arg_size = 10;
	vars->arg_idx = 0;
}

int	parse_commands(t_minishell *shell, char **parms, t_Command **commands)
{
	t_Command	*cmds;
	t_vars		vars;

	ft_init_vars(&vars);
	if (ft_init_cmds(shell, &cmds, &vars) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	while (parms[vars.idx] != NULL)
		vars.idx += ft_all_ifs(shell, &cmds, &vars, parms);
	cmds[vars.cmd_count].args[vars.arg_idx] = NULL;
	vars.cmd_count++;
	*commands = cmds;
	return (vars.cmd_count);
}

int	execute_commands(t_minishell *shell, t_Command *commands, int cmd_c)
{
	int		i;
	t_evars	evars;

	evars.cmd_count = cmd_c;
	evars.pipes = ft_calloc(sizeof(int *), (cmd_c - 1));
	ft_create_pipes(&evars, shell);
	i = 0;
	while (i < cmd_c)
	{
		evars.pid = fork();
		if (evars.pid == 0)
			ft_pid_zero(&evars, commands, shell, i);
		else if (evars.pid > 0)
		{
			if (i < cmd_c - 1)
				close(evars.pipes[i][1]);
			if (i > 0)
				close(evars.pipes[i - 1][0]);
		}
		else
			exit(EXIT_FAILURE);
		i++;
	}
	ft_close_and_await_code(&evars, shell, cmd_c);
	return (0);
}
