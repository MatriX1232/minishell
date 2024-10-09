/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:12:42 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/24 17:49:47 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libraries.h"

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
	{
		ft_error(shell, "Could not allocate memory for prefix success\n", 1);
		exit(EXIT_FAILURE);
	}
	shell->print_prefix_failure = ft_strdup("＞︿＜ minishell ▶ ");
	if (!shell->print_prefix_failure)
	{
		ft_error(shell, "Could not allocate memory for prefix failure\n", 1);
		exit(EXIT_FAILURE);
	}
	shell->cwd = (char *) malloc(1024 * sizeof(char));
	if (!shell->cwd)
	{
		ft_error(shell, "Could not allocate memory for shell.cwd\n", 1);
		exit(EXIT_FAILURE);
	}
	shell->parms = NULL;
	shell->argv = argv;
	shell->quotes = false;
	shell->env = ft_init_env(envp);
}
// deleted frees in above function to save lines - shell is freed in ft_error
// also added shell->mallocs = NULL; to initialize it

void	ft_print_parms(char **parms)
{
	int	i;

	i = 0;
	while (parms[i])
		printf("%s\n", parms[i++]);
}

static int	ft_init(t_minishell **shell, int ac, char **argv, char **envp)
{
	(void)ac;
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

int	main(int argc, char *argv[], char **envp)
{
	t_minishell	*shell;
	char		*line;

	shell = NULL;
	if (ft_init(&shell, argc, argv, envp) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	line = ft_strdup("");
	ft_add_var(shell, ft_strdup("?=0"));
	while (line)
	{
		free(line);
		line = readline(shell->print_prefix_success);
		if (line == NULL)
			return (ft_free_shell(shell), printf("exit\n"), EXIT_SUCCESS);
		if (line)
			add_history(line);
		if (ft_strncmp(line, "exit", 5) == 0)
			return (ft_free_shell(shell), printf("exit\n"), EXIT_SUCCESS);
		if (ft_check_line(line) == 1)
		{
			ft_qparser_shell(shell, line);
			ft_parse(shell, line);
			ft_free_parms(shell);
		}
	}
	return (EXIT_SUCCESS);
}
