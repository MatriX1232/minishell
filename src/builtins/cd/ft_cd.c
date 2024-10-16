/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:12:54 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/16 22:45:04 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../builtins.h"

int	ft_cd(t_minishell *shell)
{
	int		i;
	char	*msg;

	i = ft_tablen(shell->parms);
	if (i != 2)
	{
		ft_add_var(shell, ft_strdup("?=1"), 1);
		msg = ft_strdup("Usage: cd <directory>\n");
		ft_error(shell, msg, 0);
		free(msg);
		return (EXIT_FAILURE);
	}
	if (chdir(shell->parms[1]) == -1)
	{
		ft_add_var(shell, ft_strdup("?=1"), 1);
		msg = ft_strjoin("Could not change directory: ", shell->parms[1]);
		msg = ft_strjoin_free(msg, "\n", 1, 0);
		ft_error(shell, msg, 0);
		free(msg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
