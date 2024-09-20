/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 22:36:29 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/20 11:09:30 by msolinsk         ###   ########.fr       */
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

int	ft_echo(t_minishell *shell)
{
	int		i;
	int		len;

	i = 1;
	len = ft_tablen(shell->parms);
	if (shell->parms[0][4] != '\0')
		return (ft_error(shell, "Usage: echo <message>\n", 0), EXIT_FAILURE);
	if (shell->parms[1] && ft_strncmp(shell->parms[1], "-n", 2) == 0)
			i = 2;
	while (shell->parms[i])
	{
		printf("%s", shell->parms[i]);
		if (i < len)
			printf(" ");
		i++;
	}
	if (shell->parms[1] && ft_strncmp(shell->parms[1], "-n", 2) != 0)
		printf("\n");
	return (EXIT_SUCCESS);
}
