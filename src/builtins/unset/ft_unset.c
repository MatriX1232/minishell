/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 22:53:11 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/16 23:50:06 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../builtins.h"

static int	ft_not_parm(t_minishell *shell)
{
	char	*msg;

	msg = ft_strdup("Usage: unset <variable>\n");
	ft_error(shell, msg, 0);
	free(msg);
	return (EXIT_FAILURE);
}

static int	ft_unset_error(t_minishell *shell)
{
	char	*msg;

	msg = ft_strjoin("Could not unset variable: ", shell->parms[1]);
	msg = ft_strjoin_free(msg, "\n", 1, 0);
	ft_error(shell, msg, 0);
	free(msg);
	return (EXIT_FAILURE);
}

int	ft_unset(t_minishell *shell)
{
	int	i;

	if (!shell->parms[1])
		return (ft_not_parm(shell));
	i = 1;
	while (shell->parms[i])
	{
		if (ft_delete_var(shell, shell->parms[i]) == EXIT_FAILURE)
			return (ft_unset_error(shell));
		i++;
	}
	return (EXIT_SUCCESS);
}
