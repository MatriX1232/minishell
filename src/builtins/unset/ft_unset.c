/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 22:53:11 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/25 16:59:34 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../builtins.h"

static int	ft_invalid_name(t_minishell *shell, char *var)
{
	char	*msg;

	msg = ft_strjoin("Invalid variable name: ", shell->parms[1]);
	msg = ft_strjoin_free(msg, "\n");
	ft_error(shell, msg, 0);
	free(msg);
	free(var);
	return (EXIT_FAILURE);
}

static int	ft_not_parm(t_minishell *shell)
{
	char	*msg;

	msg = ft_strdup("Usage: unset <variable>\n");
	ft_error(shell, msg, 0);
	free(msg);
	return (EXIT_FAILURE);
}

int	ft_unset(t_minishell *shell)
{
	char	*var;
	char	*msg;

	if (shell->parms[1])
		var = ft_get_var_value(shell, shell->parms[1]);
	if (!shell->parms[1])
		return (ft_not_parm(shell));
	else if (!var)
		return (ft_invalid_name(shell, var));
	else if (ft_delete_var(shell, shell->parms[1]) == EXIT_FAILURE)
	{
		msg = ft_strjoin("Could not unset variable: ", shell->parms[1]);
		msg = ft_strjoin_free(msg, "\n");
		ft_error(shell, msg, 0);
		free(msg);
		free(var);
		return (EXIT_FAILURE);
	}
	free(var);
	return (EXIT_SUCCESS);
}
