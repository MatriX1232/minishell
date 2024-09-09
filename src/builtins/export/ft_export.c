/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 23:01:30 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/09 16:37:42 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../builtins.h"

int	ft_export(t_minishell *shell)
{
	char	*msg;

	if (!shell->parms[1])
	{
		msg = ft_strdup("Usage: export <variable>\n");
		ft_error(shell, msg);
		free(msg);
		return (EXIT_FAILURE);
	}
	if (setenv(shell->parms[1], "export test", 1) == -1)
	{
		msg = ft_strjoin("Could not export variable: ", shell->parms[1]);
		ft_error(shell, msg);
		free(msg);
		return (EXIT_FAILURE);
	}
	printf("Exported variable: %s | %s\n", shell->parms[1], getenv(shell->parms[1]));
	return (EXIT_SUCCESS);
}
