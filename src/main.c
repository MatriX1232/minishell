/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:12:42 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/09 18:39:31 by msolinsk         ###   ########.fr       */
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
		ft_error(NULL, "Could not allocate memory for shell\n");
		return(NULL);
	}
	return (shell);
}


static void	ft_tshell_init(t_minishell *shell, char *argv[], char **envp)
{
	shell->print_prefix_success = ft_strdup("\x1b[33m  ^_^  minishell ▶ \x1b[0m");
	shell->print_prefix_failure = ft_strdup("＞︿＜ minishell ▶ ");
	shell->cwd = (char *) malloc(1024 * sizeof(char));
	if (!shell->cwd)
	{
		ft_error(shell, "Could not allocate memory for shell.cwd\n");
		free(shell);
		exit(EXIT_FAILURE);
	}
	shell->parms = NULL;
	shell->argv = argv;
	shell->quotes = false;
	shell->env = envp;
}

void	ft_print_parms(char **parms)
{
	int	i;

	i = 0;
	while (parms[i])
		printf("%s\n", parms[i++]);
}

void	sigint_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("\x1b[33m  ^_^  minishell ▶ \x1b[0m", 0);
	rl_redisplay();
}

int	main(int argc, char *argv[], char **envp)
{
	t_minishell			*shell;
	char				*line;
	int					i;

	printf("MINISHELL\n");
	printf("argc: %d\n", argc);

	i = 0;
	while (argv[i])
	{
		printf("argv[%d]: %s\n", i, argv[i]);
		i++;
	}
	printf("\n\n");

	shell = NULL;
	shell = ft_malloc_shell(shell);
	if (shell == NULL)
		return (EXIT_FAILURE);
	ft_tshell_init(shell, argv, envp);

	signal(SIGINT, sigint_handler);
	line = readline(shell->print_prefix_success);
	if (line)
		add_history(line);
	while (line)
	{
		if (ft_strncmp(line, "exit", 4) == 0)
			return (ft_free_shell(shell), EXIT_SUCCESS);

		ft_qparser_shell(shell, line);
		ft_parse(shell, line);
		ft_free_parms(shell->parms);
		free(line);
		line = readline(shell->print_prefix_success);
		if (line)
			add_history(line);
	}
	return (EXIT_SUCCESS);
}
