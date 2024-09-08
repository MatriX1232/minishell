/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 22:53:11 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/08 23:00:36 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../builtins.h"

int	ft_unset(t_minishell *shell)
{
	char	*msg;
	if (!shell->parms[1])
	{
		msg = ft_strdup("Usage: unset <variable>\n");
		ft_error(shell, msg);
		free(msg);
		return (EXIT_FAILURE);
	}
	if (unsetenv(shell->parms[1]) == -1)
	{
		msg = ft_strjoin("Could not unset variable: ", shell->parms[1]);
		ft_error(shell, msg);
		free(msg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
