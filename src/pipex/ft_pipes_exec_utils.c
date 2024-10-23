/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipes_exec_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 16:44:23 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/23 18:07:37 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/libraries.h"
#include "../../include/structures.h"
#include "pipex.h"

void	ft_no_input_file(t_evars *evars, t_minishell *sh, t_Command *cd, int i)
{
	t_minishell	*shell;
	t_Command	*commands;

	shell = sh;
	commands = cd;
	evars->fd_in = open(commands[i].input_file, O_RDONLY);
	if (evars->fd_in < 0)
	{
		ft_error(shell, "failed to open input file", 0);
		exit(EXIT_FAILURE);
	}
	dup2(evars->fd_in, STDIN_FILENO);
	close(evars->fd_in);
}

void	ft_no_output_files(t_evars *ev, t_minishell *sh, t_Command *cmd, int i)
{
	t_evars		*evars;
	t_minishell	*shell;
	t_Command	*commands;

	evars = ev;
	shell = sh;
	commands = cmd;
	if (commands[i].append)
		evars->fd_out = open(commands[i].output_file,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		evars->fd_out = open(commands[i].output_file,
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (evars->fd_out < 0)
	{
		ft_error(shell, "failed to open output file", 0);
		exit(EXIT_FAILURE);
	}
	dup2(evars->fd_out, STDOUT_FILENO);
	close(evars->fd_out);
}

void	ft_no_heredoc_delim(t_evars *evars, t_Command *commands, int i)
{
	char	*line;

	close(evars->hd_pipe[0]);
	line = NULL;
	while (1)
	{
		ft_putstr_fd("> ", STDOUT_FILENO);
		line = get_next_line(0);
		line[ft_strlen(line) - 1] = '\0';
		if (ft_strncmp(line, commands[i].heredoc_delim,
				ft_strlen(line)) == 0)
			break ;
		write(evars->hd_pipe[1], line, ft_strlen(line));
		write(evars->hd_pipe[1], "\n", 1);
	}
	free(line);
	close(evars->hd_pipe[1]);
	exit(0);
}

void	ft_no_heredoc_main(t_evars *ev, t_minishell *sh, t_Command *cmd, int i)
{
	t_evars		*evars;
	t_minishell	*shell;
	t_Command	*commands;

	evars = ev;
	shell = sh;
	commands = cmd;
	if (pipe(evars->hd_pipe) == -1)
	{
		ft_error(shell, "pipe error", 0);
		exit(EXIT_FAILURE);
	}
	if (commands[i].heredoc_delim != NULL)
		ft_no_heredoc_delim(evars, commands, i);
	else
	{
		close(evars->hd_pipe[1]);
		dup2(evars->hd_pipe[0], STDIN_FILENO);
		close(evars->hd_pipe[0]);
		waitpid(evars->hd_pid, NULL, 0);
	}
}

void	ft_create_pipes(t_evars *evars, t_minishell *shell)
{
	int	i;

	i = 0;
	while (i < evars->cmd_count - 1)
	{
		evars->pipes[i] = ft_calloc(sizeof(int), 2);
		if (pipe(evars->pipes[i]) == -1)
		{
			ft_error(shell, "pipe error", 0);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}
