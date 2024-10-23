/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:29:48 by idomagal          #+#    #+#             */
/*   Updated: 2024/10/23 17:51:41 by msolinsk         ###   ########.fr       */
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
	{
		ft_all_ifs(shell, &cmds, &vars, parms);
		vars.idx++;
	}
	cmds[vars.cmd_count].args[vars.arg_idx] = NULL;
	vars.cmd_count++;
	*commands = cmds;
	return (vars.cmd_count);
}

void	ft_close_and_await_code(t_evars *evars, t_minishell *shell, int cmd_count)
{
	int	i;

	i = 0;
	while (i < cmd_count - 1)
	{
		close(evars->pipes[i][0]);
		close(evars->pipes[i][1]);
		free(evars->pipes[i]);
		i++;
	}
	free(evars->pipes);
	i = 0;
	evars->status = 0;
	while (i++ < cmd_count)
		wait(&evars->status);
	if (WIFEXITED(evars->status))
		ft_add_var(shell, ft_strjoin_free("?=", ft_itoa(WEXITSTATUS(evars->status)), 0, 1), 1);
	else if (WIFSIGNALED(evars->status))
		ft_add_var(shell, ft_strjoin_free("?=", ft_itoa(128 + WTERMSIG(evars->status)), 0, 1), 1);
}

void	ft_free_pipes_built_exec(t_evars *evars, t_Command *commands, t_minishell *shell, int i)
{
	int	j;

	j = 0;
	while (j < evars->cmd_count - 1)
	{
		close(evars->pipes[j][0]);
		close(evars->pipes[j][1]);
		j++;
	}
	if (is_builtin(commands[i].args[0]))
	{
		execute_builtin(shell, commands[i].args);
		exit(EXIT_SUCCESS);
	}
	else
	{
		execve(get_exe(commands[i].args[0],
				shell->env[get_path(shell->env)]),
				commands[i].args, shell->env);
		ft_error(shell, "execve error\n", 0);
		exit(EXIT_FAILURE);
	}
}

void	ft_pid_zero(t_evars *evars, t_Command *cmds, t_minishell *sh, int i)
{
	if (cmds[i].input_file != NULL)
		ft_no_input_file(evars, sh, cmds, i);
	if (cmds[i].output_file != NULL)
		ft_no_output_files(evars, sh, cmds, i);
	if (cmds[i].heredoc_delim != NULL)
		ft_no_heredoc_main(evars, sh, cmds, i);
	if (i > 0)
		dup2(evars->pipes[i - 1][0], STDIN_FILENO);
	if (i < evars->cmd_count - 1)
		dup2(evars->pipes[i][1], STDOUT_FILENO);
	ft_free_pipes_built_exec(evars, cmds, sh, i);
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
		i++;
	}
	ft_close_and_await_code(&evars, shell, cmd_c);
	return (0);
}
