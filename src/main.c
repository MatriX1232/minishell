/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:12:42 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/07 21:11:30 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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


static void	ft_tshell_init(t_minishell *shell, char *argv[])
{
	shell->cwd = (char *) malloc(1024 * sizeof(char));
	if (!shell->cwd)
	{
		ft_error(shell, "Could not allocate memory for shell.cwd\n");
		free(shell);
		exit(EXIT_FAILURE);
	}
	shell->print_prefix_success = ft_strdup("\x1b[33m^_^ minishell ▶ \x1b[0m");
	shell->print_prefix_failure = ft_strdup("＞︿＜ minishell ▶");
	shell->parms = NULL;
	shell->argv = argv;
}

int	main(int argc, char *argv[])
{
	t_minishell	*shell;
	int	i;

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
	ft_tshell_init(shell, argv);

	if (ft_pwd(shell) == EXIT_FAILURE)
		return (ft_free_shell(shell), EXIT_FAILURE);

	return (EXIT_SUCCESS);
}
