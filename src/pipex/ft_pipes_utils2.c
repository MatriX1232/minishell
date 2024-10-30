/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:39:38 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/23 18:02:16 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/libraries.h"
#include "../../include/structures.h"
#include "pipex.h"

int	ft_append_if(t_Command **cmds, t_vars *vars, char **ps)
{
	(*cmds)[vars->cmd_count].output_file = ps[vars->idx + 1];
	(*cmds)[vars->cmd_count].append = 1;
	return (2);
}

int	ft_no_append_if(t_Command **cmds, t_vars *vars, char **ps)
{
	(*cmds)[vars->cmd_count].output_file = ps[vars->idx + 1];
	(*cmds)[vars->cmd_count].append = 0;
	return (2);
}

int	ft_all_ifs(t_minishell *sh, t_Command **cmds, t_vars *vars, char **ps)
{
	int	token;

	token = 1;
	if (vars->cmd_count >= vars->cmds_size)
		ft_cc_more_cs(sh, cmds, vars);
	if (ft_strncmp(ps[vars->idx], "|", 2) == 0 && cmds == NULL)
		ft_if_pipe(cmds, &vars->cmd_count, &vars->arg_idx, &vars->arg_size);
	else if (ft_strncmp(ps[vars->idx], "<<", 3) == 0)
	{
		(*cmds)[vars->cmd_count].heredoc_delim = ps[vars->idx + 1];
		token = 2;
	}
	else if (ft_strncmp(ps[vars->idx], "<", 2) == 0)
		token = ft_if_first_red(sh, cmds, vars, ps);
	else if (ft_strncmp(ps[vars->idx], ">>", 3) == 0)
		token = ft_append_if(cmds, vars, ps);
	else if (ft_strncmp(ps[vars->idx], ">", 2) == 0)
		token = ft_no_append_if(cmds, vars, ps);
	else
	{
		ft_last_else(sh, cmds, vars);
		(*cmds)[vars->cmd_count].args[vars->arg_idx++] = ps[vars->idx];
	}
	return (token);
}

void	ft_handle_heredoc_parent(t_evars *evars)
{
	close(evars->hd_pipe[1]);
	waitpid(evars->hd_pid, NULL, 0);
	dup2(evars->hd_pipe[0], STDIN_FILENO);
	close(evars->hd_pipe[0]);
}

void	ft_handle_heredoc_child(t_evars *evars, t_Command *commands, int i)
{
	close(evars->hd_pipe[0]);
	ft_no_heredoc_delim(evars, commands, i);
}
