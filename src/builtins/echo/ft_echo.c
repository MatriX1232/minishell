/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 22:36:29 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/11 15:53:30 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"
#include "../../../include/minishell.h"

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
	if (shell->quotes == false)
	{
		while (shell->parms[i])
		{
			printf("%s", shell->parms[i]);
			if (i < len - 1)
				printf(" ");
			i++;
		}
	}
	else
		printf("%s", shell->parms[1]);
	printf("\n");
	return (EXIT_SUCCESS);
}
