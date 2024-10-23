/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_exec_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:11:09 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/23 18:20:11 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/libraries.h"
#include "../../include/structures.h"
#include "pipex.h"

void	ft_close_and_await_code(t_evars *ev, t_minishell *sh, int cmd_c)
{
	int			i;
	t_evars		*evars;
	t_minishell	*shell;

	evars = ev;
	shell = sh;
	i = 0;
	while (i < cmd_c - 1)
	{
		close(evars->pipes[i][0]);
		close(evars->pipes[i][1]);
		free(evars->pipes[i]);
		i++;
	}
	free(evars->pipes);
	i = 0;
	evars->status = 0;
	while (i < cmd_c)
	{
		wait(&evars->status);
		i++;
	}
	if (WIFEXITED(evars->status))
		ft_add_var(shell, ft_strjoin_free("?=", \
		ft_itoa(WEXITSTATUS(evars->status)), 0, 1), 1);
	else if (WIFSIGNALED(evars->status))
		ft_add_var(shell, ft_strjoin_free("?=", \
		ft_itoa(128 + WTERMSIG(evars->status)), 0, 1), 1);
}

void	ft_free_pip_bi_e(t_evars *ev, t_Command *cmd, t_minishell *shell, int i)
{
	t_evars		*evars;
	int			j;

	evars = ev;
	j = 0;
	while (j < evars->cmd_count - 1)
	{
		close(evars->pipes[j][0]);
		close(evars->pipes[j][1]);
		j++;
	}
	if (is_builtin(cmd[i].args[0]))
	{
		execute_builtin(shell, cmd[i].args);
		exit(EXIT_SUCCESS);
	}
	else
	{
		execve(get_exe(cmd[i].args[0],
				shell->env[get_path(shell->env)]), \
				cmd[i].args, shell->env);
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
	{
		dup2(evars->pipes[i - 1][0], STDIN_FILENO);
		close(evars->pipes[i - 1][1]);
	}
	if (i < evars->cmd_count - 1)
	{
		dup2(evars->pipes[i][1], STDOUT_FILENO);
		close(evars->pipes[i][0]);
	}
	ft_free_pip_bi_e(evars, cmds, sh, i);
}
