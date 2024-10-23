/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:39:38 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/23 16:40:10 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/libraries.h"
#include "../../include/structures.h"
#include "pipex.h"

void	ft_all_ifs(t_minishell *shell, t_Command **cmds, t_vars *vars, char **parms)
{
	if (vars->cmd_count >= vars->cmds_size)
		ft_cc_more_cs(shell, cmds, vars);
	if (ft_strncmp(parms[vars->idx], "|", 2) == 0)
		ft_if_pipe(cmds, vars->cmd_count, &vars->arg_idx, &vars->arg_size);
	else if (ft_strncmp(parms[vars->idx], "<<", 3) == 0)
		(*cmds)[vars->cmd_count].heredoc_delim = parms[vars->idx + 1];
	else if (ft_strncmp(parms[vars->idx], "<", 2) == 0)
		ft_if_first_redirect(shell, cmds, vars, parms);
	else if (ft_strncmp(parms[vars->idx], ">>", 3) == 0)
	{
		(*cmds)[vars->cmd_count].output_file = parms[vars->idx + 1];
		(*cmds)[vars->cmd_count].append = 1;
	}
	else if (ft_strncmp(parms[vars->idx], ">", 2) == 0)
	{
		(*cmds)[vars->cmd_count].output_file = parms[vars->idx + 1];
		(*cmds)[vars->cmd_count].append = 0;
	}
	else
	{
		ft_last_else(shell, cmds, vars);
		(*cmds)[vars->cmd_count].args[vars->arg_idx++] = parms[vars->idx];
	}
}
