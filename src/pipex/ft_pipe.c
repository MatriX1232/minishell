/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 10:29:48 by idomagal          #+#    #+#             */
/*   Updated: 2024/10/07 19:36:01 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/structures.h"
#include "../../include/minishell.h"

int	parse_commands(t_minishell *shell, char **parms, Command **commands)
{
	int			cmd_count;
	int			idx;
	int			cmds_size;
	int			arg_size;
	int			arg_idx;
	Command		*cmds;

	idx = 0;
	cmd_count = 0;
	cmds_size = 10;
	cmds = ft_calloc(sizeof(Command), cmds_size);
	if (cmds == NULL)
	{
		ft_error(shell, "malloc error", 0);
		exit(EXIT_FAILURE);
	}
	cmds[cmd_count].args = ft_calloc(sizeof(char *), 10);
	cmds[cmd_count].input_file = NULL;
	cmds[cmd_count].output_file = NULL;
	cmds[cmd_count].heredoc_delim = NULL;
	cmds[cmd_count].append = 0;
	arg_size = 10;
	arg_idx = 0;
	while (parms[idx] != NULL)
	{
		if (cmd_count >= cmds_size)
		{
			cmds_size *= 2;
			cmds = ft_realloc(cmds, sizeof(Command) * cmds_size,
				sizeof(Command) * (cmds_size / 2));
			if (cmds == NULL)
			{
				ft_error(shell, "realloc error", 0);
				exit(EXIT_FAILURE);
			}
		}
		if (ft_strncmp(parms[idx], "|", 2) == 0)
		{
			cmds[cmd_count].args[arg_idx] = NULL;
			cmd_count++;
			cmds[cmd_count].args = ft_calloc(sizeof(char *), 10);
			cmds[cmd_count].input_file = NULL;
			cmds[cmd_count].output_file = NULL;
			cmds[cmd_count].heredoc_delim = NULL;
			cmds[cmd_count].append = 0;
			arg_size = 10;
			arg_idx = 0;
		}
		else if (ft_strncmp(parms[idx], "<", 2) == 0)
		{
			idx++;
			cmds[cmd_count].input_file = parms[idx];
		}
		else if (ft_strncmp(parms[idx], "<<", 3) == 0)
		{
			idx++;
			cmds[cmd_count].heredoc_delim = parms[idx];
		}
		else if (ft_strncmp(parms[idx], ">", 2) == 0)
		{
			idx++;
			cmds[cmd_count].output_file = parms[idx];
			cmds[cmd_count].append = 0;
		}
		else if (ft_strncmp(parms[idx], ">>", 3) == 0)
		{
			idx++;
			cmds[cmd_count].output_file = parms[idx];
			cmds[cmd_count].append = 1;
		}
		else
		{
			if (arg_idx >= arg_size - 1)
			{
				arg_size *= 2;
				cmds[cmd_count].args = ft_realloc(cmds[cmd_count].args,
						sizeof(char *) * arg_size, sizeof(char *) * (arg_size / 2));
				if (cmds[cmd_count].args == NULL)
				{
					ft_error(shell, "realloc error", 0);
					exit(EXIT_FAILURE);
				}
			}
			cmds[cmd_count].args[arg_idx++] = parms[idx];
		}
		idx++;
	}
	cmds[cmd_count].args[arg_idx] = NULL;
	cmd_count++;
	*commands = cmds;
	return (cmd_count);
}

int	execute_commands(t_minishell *shell, Command *commands, int cmd_count)
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
			execve(get_exe(commands[i].args[0],
					shell->env[get_path(shell->env)]),
					commands[i].args, shell->env);
			ft_error(shell, "execve error", 0);
			exit(EXIT_FAILURE);
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
		ft_add_var(shell, ft_strjoin_free("?=", ft_itoa(WEXITSTATUS(status)), 0, 1));
	else if (WIFSIGNALED(status))
		ft_add_var(shell, ft_strjoin_free("?=", ft_itoa(128 + WTERMSIG(status)), 0, 1));
	return (0);
}

int	ft_detect_pipe(t_minishell *shell)
{
	int			i;

	i = 0;
	shell->pipe.count = 0;
	while (shell->parms[i])
	{
		if (ft_strncmp(shell->parms[i], "|", 2) == 0
			|| ft_strncmp(shell->parms[i], ">", 2) == 0
			|| ft_strncmp(shell->parms[i], ">>", 3) == 0
			|| ft_strncmp(shell->parms[i], "<", 2) == 0
			|| ft_strncmp(shell->parms[i], "<<", 3) == 0)
			shell->pipe.count++;
		i++;
	}
	if (shell->pipe.count > 0)
		return (1);
	return (0);
}
