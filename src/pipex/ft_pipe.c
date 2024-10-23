/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:29:48 by idomagal          #+#    #+#             */
/*   Updated: 2024/10/23 16:32:51 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/structures.h"
#include "../../include/minishell.h"
#include "../../include/libraries.h"
#include "pipex.h"

static void	ft_if_pipe(t_Command **cmds, int cmdc, int *ax, int *as)
{
	(*cmds)[cmdc].args[*ax] = NULL;
	cmdc++;
	(*cmds)[cmdc].args = ft_calloc(sizeof(char *), 10);
	(*cmds)[cmdc].input_file = NULL;
	(*cmds)[cmdc].output_file = NULL;
	(*cmds)[cmdc].heredoc_delim = NULL;
	(*cmds)[cmdc].append = 0;
	*as = 10;
	*ax = 0;
}

static int	ft_init_cmds(t_minishell *shell, t_Command **cmds, t_vars *vars)
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

static void	ft_cc_more_cs(t_minishell *shell, t_Command **cmds, t_vars *vars)
{
	vars->cmds_size *= 2;
	cmds = ft_realloc(cmds, sizeof(t_Command) * (vars->cmds_size),
		sizeof(t_Command) * (vars->cmds_size / 2));
	if (cmds == NULL)
	{
		ft_error(shell, E_MALLOC, 0);
		exit(EXIT_FAILURE);
	}
}

static void	ft_last_else(t_minishell *shell, t_Command **cmds, t_vars *vars)
{
	if (vars->arg_idx >= vars->arg_size - 1)
	{
		vars->arg_size *= 2;
		(*cmds)[vars->cmd_count].args = ft_realloc((*cmds)[vars->cmd_count].args,
				sizeof(char *) * vars->arg_size, sizeof(char *) * (vars->arg_size / 2));
		if ((*cmds)[vars->cmd_count].args == NULL)
		{
			ft_error(shell, "realloc error", 0);
			exit(EXIT_FAILURE);
		}
	}
}

static void	ft_init_vars(t_vars *vars)
{
	vars->cmd_count = 0;
	vars->cmds_size = 10;
	vars->idx = 0;
	vars->arg_size = 10;
	vars->arg_idx = 0;
}

void	ft_if_first_redirect(t_minishell *shell, t_Command **cmds, t_vars *vars, char **parms)
{
	(*cmds)[vars->cmd_count].input_file = parms[vars->idx + 1];
	if (access((*cmds)[vars->cmd_count].input_file, F_OK) != 0)
	{
		ft_error(shell, "input file not found", 0);
		ft_add_var(shell, ft_strjoin_free("?=", "1", 0, 1), 1);
	}
}

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

int	execute_commands(t_minishell *shell, t_Command *commands, int cmd_count)
{
	int		i;
	int		j;
	int		fd_in;
	int		fd_out;
	int		**pipes;
	pid_t	pid;
	pid_t	hd_pid;
	int		hd_pipe[2];
	char	*line;
	int		status;

	pipes = ft_calloc(sizeof(int *), (cmd_count - 1));
	i = 0;
	while (i < cmd_count - 1)
	{
		pipes[i] = ft_calloc(sizeof(int), 2);
		if (pipe(pipes[i]) == -1)
		{
			ft_error(shell, "pipe error", 0);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	i = 0;
	while (i < cmd_count)
	{
		pid = fork();
		if (pid == 0)
		{
			if (commands[i].input_file != NULL)
			{
				fd_in = open(commands[i].input_file, O_RDONLY);
				if (fd_in < 0)
				{
					ft_error(shell, "failed to open input file", 0);
					exit(EXIT_FAILURE);
				}
				dup2(fd_in, STDIN_FILENO);
				close(fd_in);
			}
			if (commands[i].output_file != NULL)
			{
				if (commands[i].append)
					fd_out = open(commands[i].output_file,
							O_WRONLY | O_CREAT | O_APPEND, 0644);
				else
					fd_out = open(commands[i].output_file,
							O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd_out < 0)
				{
					ft_error(shell, "failed to open output file", 0);
					exit(EXIT_FAILURE);
				}
				dup2(fd_out, STDOUT_FILENO);
				close(fd_out);
			}
			if (commands[i].heredoc_delim != NULL)
			{
				if (pipe(hd_pipe) == -1)
				{
					ft_error(shell, "pipe error", 0);
					exit(EXIT_FAILURE);
				}
				hd_pid = fork();
				if (hd_pid == 0)
				{
					close(hd_pipe[0]);
					line = NULL;
					while (1)
					{
						ft_putstr_fd("> ", STDOUT_FILENO);
						line = get_next_line(0);
						line[ft_strlen(line) - 1] = '\0';
						if (ft_strncmp(line, commands[i].heredoc_delim,
								ft_strlen(line)) == 0)
							break ;
						write(hd_pipe[1], line, ft_strlen(line));
						write(hd_pipe[1], "\n", 1);
					}
					free(line);
					close(hd_pipe[1]);
					exit(0);
				}
				else
				{
					close(hd_pipe[1]);
					dup2(hd_pipe[0], STDIN_FILENO);
					close(hd_pipe[0]);
					waitpid(hd_pid, NULL, 0);
				}
			}
			if (i > 0)
				dup2(pipes[i - 1][0], STDIN_FILENO);
			if (i < cmd_count - 1)
				dup2(pipes[i][1], STDOUT_FILENO);
			j = 0;
			while (j < cmd_count - 1)
			{
				close(pipes[j][0]);
				close(pipes[j][1]);
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
		i++;
	}
	i = 0;
	while (i < cmd_count - 1)
	{
		close(pipes[i][0]);
		close(pipes[i][1]);
		free(pipes[i]);
		i++;
	}
	free(pipes);
	i = 0;
	status = 0;
	while (i++ < cmd_count)
		wait(&status);
	if (WIFEXITED(status))
		ft_add_var(shell, ft_strjoin_free("?=", ft_itoa(WEXITSTATUS(status)), 0, 1), 1);
	else if (WIFSIGNALED(status))
		ft_add_var(shell, ft_strjoin_free("?=", ft_itoa(128 + WTERMSIG(status)), 0, 1), 1);
	return (0);
}
