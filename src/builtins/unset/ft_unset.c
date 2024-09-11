/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 22:53:11 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/11 15:13:48 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../builtins.h"

int	ft_unset(t_minishell *shell)
{
	char	*msg;

	if (!shell->parms[1] || shell->parms[0][5] != '\0')
	{
		msg = ft_strdup("Usage: unset <variable>\n");
		ft_error(shell, msg, 0);
		free(msg);
		return (EXIT_FAILURE);
	}
	else if (ft_delete_var(shell, shell->parms[1]) == EXIT_FAILURE)
	{
		msg = ft_strjoin("Could not unset variable: ", shell->parms[1]);
		ft_error(shell, msg, 0);
		free(msg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
