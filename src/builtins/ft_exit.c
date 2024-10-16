/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 22:24:42 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/16 22:43:59 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../quotes/quotes.h"

static int free_exit(t_minishell *shell, char *line, char *msg, int exit_code)
{
	ft_error(shell, msg, 0);
	ft_free_shell(shell);
	free(line);
	return (exit_code);
}

void	ft_exit(t_minishell *shell, char *line)
{
	int	i;

	if (!shell->parms[1])
		exit(free_exit(shell, line, NULL, 0));
	if (shell->parms[2])
		exit(free_exit(shell, line, "too many arguments\n", 1));
	i = 0;
	while (shell->parms[1][i])
	{
		if (!ft_isdigit(shell->parms[1][i]) && !ft_intab(shell->parms[1][i], " +-"))
			exit(free_exit(shell, line, "numeric argument required\n", 2));
		i++;
	}
	ft_free_shell(shell);
	free(line);
	exit(ft_atoi(shell->parms[1]));
}
