/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:37:29 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/23 17:50:25 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/libraries.h"
#include "../../include/structures.h"
#include "pipex.h"

void	ft_if_pipe(t_Command **cmds, int *cmdc, int *ax, int *as)
{
	(*cmds)[*cmdc].args[*ax] = NULL;
	(*cmdc)++;
	(*cmds)[*cmdc].args = ft_calloc(sizeof(char *), 10);
	(*cmds)[*cmdc].input_file = NULL;
	(*cmds)[*cmdc].output_file = NULL;
	(*cmds)[*cmdc].heredoc_delim = NULL;
	(*cmds)[*cmdc].append = 0;
	*as = 10;
	*ax = 0;
}

int	ft_init_cmds(t_minishell *shell, t_Command **cmds, t_vars *vars)
{
	(*cmds) = ft_calloc(sizeof(t_Command), vars->cmds_size);
	if ((*cmds) == NULL)
		return (ft_error(shell, E_MALLOC, 0), exit(EXIT_FAILURE), EXIT_FAILURE);
	(*cmds)[vars->cmd_count].args = ft_calloc(sizeof(char *), 10);
	(*cmds)[vars->cmd_count].input_file = NULL;
	(*cmds)[vars->cmd_count].output_file = NULL;
	(*cmds)[vars->cmd_count].heredoc_delim = NULL;
	(*cmds)[vars->cmd_count].append = 0;
	return (EXIT_SUCCESS);
}

void ft_cc_more_cs(t_minishell *shell, t_Command **cmds, t_vars *vars)
{
	vars->cmds_size *= 2;
	*cmds = ft_realloc(*cmds, sizeof(t_Command) * vars->cmds_size, 
											sizeof(t_Command) * (vars->cmds_size / 2));
	if (*cmds == NULL)
	{
		ft_error(shell, E_MALLOC, 0);
		exit(EXIT_FAILURE);
	}
}

void	ft_last_else(t_minishell *shell, t_Command **cmds, t_vars *vars)
{
	if (vars->arg_idx >= vars->arg_size - 1)
	{
		vars->arg_size *= 2;
		(*cmds)[vars->cmd_count].args = \
				ft_realloc((*cmds)[vars->cmd_count].args,
				sizeof(char *) * vars->arg_size, sizeof(char *) * \
				(vars->arg_size / 2));
		if ((*cmds)[vars->cmd_count].args == NULL)
		{
			ft_error(shell, "realloc error\n", 0);
			exit(EXIT_FAILURE);
		}
	}
}

int	ft_if_first_red(t_minishell *sh, t_Command **cd, t_vars *vs, char **p)
{
	(*cd)[vs->cmd_count].input_file = p[vs->idx + 1];
	if (access((*cd)[vs->cmd_count].input_file, F_OK) != 0)
	{
		ft_error(sh, "input file not found\n", 0);
		ft_add_var(sh, ft_strjoin_free("?=", "1", 0, 0), 1);
	}
	return (2);
}
