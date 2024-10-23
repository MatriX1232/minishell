/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:12:42 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/23 11:07:44 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libraries.h"
#include "quotes/quotes.h"

/*
	Allocate memory for the shell structure

	Return SUCCESS:
		Pointer to the allocated memory

	Return FAILURE:
		NULL
*/
t_minishell	*ft_malloc_shell(t_minishell *shell)
{
	shell = (t_minishell *) malloc(1 * sizeof(t_minishell));
	if (!shell)
	{
		ft_error(NULL, "Could not allocate memory for shell\n", 1);
		return (NULL);
	}
	return (shell);
}

static void	ft_tshell_init(t_minishell *shell, char *argv[], char **envp)
{
	shell->print_prefix_success = NULL;
	shell->print_prefix_failure = NULL;
	shell->cwd = NULL;
	shell->print_prefix_success = ft_strdup("\x1b[33m^_^  minishell ▶ \x1b[0m");
	if (!shell->print_prefix_success)
		return (ft_error(shell, E_MALLOC, 1), exit(EXIT_FAILURE));
	shell->print_prefix_failure = ft_strdup("＞︿＜ minishell ▶ ");
	if (!shell->print_prefix_failure)
		return (ft_error(shell, E_MALLOC, 1), exit(EXIT_FAILURE));
	shell->cwd = (char *) malloc(2048 * sizeof(char));
	if (!shell->cwd)
		return (ft_error(shell, E_MALLOC, 1), exit(EXIT_FAILURE));
	shell->parms = NULL;
	shell->argv = argv;
	shell->env = ft_init_env(envp);
}

static int	ft_init(t_minishell **shell, int ac, char **argv, char **envp)
{
	(void)ac;
	printf("\n");
	outline("MINISHELL", "Welcome to our MINISHELL project :)",
		RED, CYAN);
	*shell = ft_malloc_shell(*shell);
	if (*shell == NULL)
		return (EXIT_FAILURE);
	ft_tshell_init(*shell, argv, envp);
	signal(SIGINT, sig_ctrlc);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTERM, sig_term);
	signal(SIGSEGV, sig_segv);
	signal(SIGABRT, sig_abort);
	return (EXIT_SUCCESS);
}

static int	ft_on_exit(t_minishell *shell, char *line)
{
	printf("exit\n");
	free(line);
	ft_free_shell(shell);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[], char **envp)
{
	t_minishell	*shell;
	char		*line;

	shell = NULL;
	if (ft_init(&shell, argc, argv, envp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	line = ft_strdup("");
	while (line)
	{
		free(line);
		line = readline(shell->print_prefix_success);
		if (line == NULL)
			return (ft_free_shell(shell), printf("exit\n"), EXIT_SUCCESS);
		if (line)
			add_history(line);
		if (ft_strncmp(line, "exit", 5) == 0)
			break ;
		if (ft_check_line(line) == 1)
		{
			ft_qparser_shell(shell, line);
			ft_parse(shell, line);
			ft_free_parms(shell);
		}
	}
	return (ft_on_exit(shell, line));
}
