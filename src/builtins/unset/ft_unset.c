/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 22:53:11 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/22 18:23:33 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../builtins.h"

int	ft_unset(t_minishell *shell)
{
	char	*var;
	char	*msg;

	if (shell->parms[1])
		var = ft_get_var_value(shell, shell->parms[1]);
	if (!shell->parms[1])
	{
		msg = ft_strdup("Usage: unset <variable>\n");
		ft_error(shell, msg, 0);
		free(msg);
		return (EXIT_FAILURE);
	}
	else if (!var)
	{
		msg = ft_strjoin("Invalid variable name: ", shell->parms[1]);
		msg = ft_strjoin_free(msg, "\n");
		ft_error(shell, msg, 0);
		free(msg);
		free(var);
		return (EXIT_FAILURE);
	}
	else if (ft_delete_var(shell, shell->parms[1]) == EXIT_FAILURE)
	{
		msg = ft_strjoin("Could not unset variable: ", shell->parms[1]);
		msg = ft_strjoin_free(msg, "\n");
		ft_error(shell, msg, 0);
		free(msg);
		free(var);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
