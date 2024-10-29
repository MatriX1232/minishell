/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:12:42 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/27 23:20:02 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libraries.h"
#include "quotes/quotes.h"
#include "builtins/builtins.h"

static int	ft_on_exit(t_minishell *shell, char *line)
{
	printf("exit\n");
	free(line);
	ft_free_shell(shell);
	rl_clear_history();
	return (EXIT_SUCCESS);
}

static char	*ft_readline(t_minishell *shell)
{
	char	*line;

	if (isatty(STDIN_FILENO))
		line = readline(shell->print_prefix_success);
	else
	{
		printf("%s", shell->print_prefix_success);
		line = get_next_line(STDIN_FILENO);
	}
	if (line)
		add_history(line);
	return (line);
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
		line = ft_readline(shell);
		if (line == NULL)
			return (ft_free_shell(shell), printf("exit\n"), EXIT_SUCCESS);
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
