/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_move_parms.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:39:13 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/22 17:47:01 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parms.h"

void	ft_add_parm(t_minishell *shell, int idx, char *value)
{
	int		i;
	int		j;
	int		len_parms;
	char	**new_parms;

	len_parms = ft_tablen(shell->parms, 0);
	new_parms = (char **) malloc((len_parms + 2) * sizeof(char *));
	if (!new_parms)
		return (ft_error(shell, E_MALLOC, 1));
	i = 0;
	j = 0;
	while (i < len_parms + 1)
	{
		if (i == idx)
		{
			new_parms[i] = value;
			free(value);
		}
		else
			new_parms[i] = ft_strdup(shell->parms[j++]);
		i++;
	}
	new_parms[i] = NULL;
	ft_free_env(shell->parms);
	shell->parms = new_parms;
}

void	ft_rm_parm(t_minishell *shell, int idx)
{
	int		i;
	int		len_parms;
	char	**new_parms;

	len_parms = ft_tablen(shell->parms, 0);
	new_parms = (char **) malloc((len_parms + 1) * sizeof(char *));
	if (!new_parms)
		return (ft_error(shell, E_MALLOC, 1));
	i = 0;
	while (i < len_parms)
	{
		if (i < idx)
			new_parms[i] = ft_strdup(shell->parms[i]);
		else if (i > idx)
			new_parms[i - 1] = ft_strdup(shell->parms[i]);
		i++;
	}
	new_parms[i] = NULL;
	ft_free_env(shell->parms);
	shell->parms = new_parms;
}
