/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:12:54 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/24 11:02:52 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../builtins.h"

int	ft_cd(t_minishell *shell)
{
	int		i;
	char	*dir;
	char	*msg;

	i = ft_tablen(shell->parms, 0);
	if (i != 2)
		dir = ft_strdup(ft_get_var_value(shell, "HOME"));
	else
		dir = ft_strdup(shell->parms[1]);
	if (chdir(dir) == -1)
	{
		ft_add_var(shell, ft_strdup("?=1"), 1);
		msg = ft_strjoin("Could not change directory: ", dir);
		msg = ft_strjoin_free(msg, "\n", 1, 0);
		ft_error(shell, msg, 0);
		free(msg);
		free(dir);
		return (EXIT_FAILURE);
	}
	free(dir);
	return (EXIT_SUCCESS);
}
