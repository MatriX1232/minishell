/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 22:36:29 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/30 11:36:08 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"
#include "../../../include/minishell.h"

int	ft_echo(t_minishell *shell)
{
	int		i;
	int		len;

	i = 1;
	len = ft_tablen(shell->parms, 1);
	if (shell->parms[1] && ft_strncmp(shell->parms[1], "-n", 3) == 0)
		i = 2;
	while (i < len)
	{
		ft_putstr_fd(shell->parms[i], STDOUT_FILENO);
		if (i < len - 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (shell->parms[1] && ft_strncmp(shell->parms[1], "-n", 3) != 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	else if (!shell->parms[1])
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (ft_add_var(shell, "?=0", 1), EXIT_SUCCESS);
}
