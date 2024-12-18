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

void	ft_exit_code(t_minishell *shell, int status)
{
	char	*temp;
	int		code;

	temp = NULL;
	if (WIFEXITED(status))
	{
		code = WEXITSTATUS(status);
		temp = ft_strjoin_free("?=", ft_itoa(code), 0, 1);
		ft_add_var(shell, temp, 1);
		free(temp);
	}
	else if (WIFSIGNALED(status))
	{
		code = 128 + WTERMSIG(status);
		temp = ft_strjoin_free("?=", ft_itoa(code), 0, 1);
		ft_add_var(shell, temp, 1);
		free(temp);
	}
}

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
	while (i++ < cmd_c)
		wait(&evars->status);
	ft_exit_code(shell, evars->status);
}

void	ft_free_pip_bi_e(t_evars *ev, t_Command *cmd, t_minishell *shell, int i)
{
	int			j;

	j = 0;
	while (j < ev->cmd_count - 1)
	{
		close(ev->pipes[j][0]);
		close(ev->pipes[j][1]);
	}
	free(ev->pipes);
	if (is_builtin(cmd[i].args[0]))
	{
		execute_builtin(shell, cmd[i].args);
		free(cmd[i].args);
		free(cmd);
		ft_free_shell(shell);
		exit(EXIT_SUCCESS);
	}
	else
	{
		execve(get_exe(cmd[i].args[0], shell->env[get_path(shell->env)]), \
				cmd[i].args, shell->env);
		ft_error(shell, "execve error\n", 1);
		ft_free_shell(shell);
		exit(EXIT_FAILURE);
	}
}

void	ft_pid_zero(t_evars *evars, t_Command *cmds, t_minishell *sh, int i)
{
	int		j;

	if (cmds[i].heredoc_delim != NULL)
		ft_no_heredoc_main(evars, sh, cmds, i);
	else if (cmds[i].input_file != NULL)
		ft_no_input_file(evars, sh, cmds, i);
	else if (i > 0)
		dup2(evars->pipes[i - 1][0], STDIN_FILENO);
	if (cmds[i].output_file != NULL)
		ft_no_output_files(evars, sh, cmds, i);
	else if (i < evars->cmd_count - 1)
		dup2(evars->pipes[i][1], STDOUT_FILENO);
	j = 0;
	while (j < evars->cmd_count - 1)
	{
		close(evars->pipes[j][0]);
		close(evars->pipes[j][1]);
		j++;
	}
	ft_free_pip_bi_e(evars, cmds, sh, i);
}
