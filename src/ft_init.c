/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 14:20:53 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/27 14:38:40 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libraries.h"
#include "quotes/quotes.h"
#include "builtins/builtins.h"

static t_minishell	*ft_malloc_shell(t_minishell *shell)
{
	shell = (t_minishell *) malloc(1 * sizeof(t_minishell));
	if (!shell)
	{
		ft_error(NULL, "Could not allocate memory for shell\n", 1);
		return (NULL);
	}
	return (shell);
}

void	ft_tshell_init(t_minishell *shell, char *argv[], char **envp)
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

int	ft_init(t_minishell **shell, int ac, char **argv, char **envp)
{
	(void)ac;
	printf("\n");
	outline("MINISHELL", "Welcome to our MINISHELL project!", \
	RED, YELLOW);
	outline("AUTHORS", "idomagal | msolinsk", GREEN, GREEN);
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
