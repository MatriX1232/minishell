/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:12:54 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/08 23:12:21 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../../../include/libraries.h"
#include "../builtins.h"

static int	ft_tablen(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	ft_cd(t_minishell *shell)
{
	int		i;
	char	*msg;

	i = ft_tablen(shell->parms);
	if (i != 2)
	{
		msg = ft_strdup("Usage: cd <directory>\n");
		ft_error(shell, msg);
		free(msg);
		return (EXIT_FAILURE);
	}
	// shell->parms[1] = ft_strtrim(shell->parms[1], "\n");
	// printf("Changing directory to: <%s>\n", shell->parms[1]);
	if (chdir(shell->parms[1]) == -1)
	{
		msg = ft_strjoin("Could not change directory: ", shell->parms[1]);
		ft_error(shell, msg);
		free(msg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}