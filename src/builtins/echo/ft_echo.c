/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 22:36:29 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/08 23:16:31 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"

static int	ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

// TODO: Implement the -n flag function
int	ft_echo(t_minishell *shell)
{
	int		i;
	int		len;

	i = 1;
	len = ft_tablen(shell->parms);
	if (shell->parms[0][4] != '\0')
	{
		ft_error(shell, "Usage: echo <message>\n", 0);
		return (EXIT_FAILURE);
	}
	while (shell->parms[i])
	{
		printf("%s", shell->parms[i]);
		if (i < len - 1)
			printf(" ");
		i++;
	}
	printf("\n");
	return (EXIT_SUCCESS);
}
