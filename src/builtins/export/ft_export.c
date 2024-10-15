/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 23:01:30 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/14 14:42:36 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../builtins.h"

static void	ft_print_parms(char **parms)
{
	int		i;
	char	**split;

	i = 0;
	while (parms[i])
	{
		split = ft_split(parms[i], '=');
		if (!split)
			printf("%sERROR: split\n%s", RED, END);
		else
			printf("declare -x %s=\"%s\"\n", split[0], split[1]);
		ft_free_env(split);
		i++;
	}
}

int	ft_export(t_minishell *shell)
{
	char	*msg;

	if (!shell->parms[1])
		ft_print_parms(shell->env);
	else if (shell->parms[1] && ft_strchr(shell->parms[1], '=') == NULL)
	{
		msg = ft_strdup("Usage: export <variable> | <variable> is optional\n");
		ft_error(shell, msg, 0);
		free(msg);
		return (EXIT_FAILURE);
	}
	else if (ft_add_var(shell, shell->parms[1]) == EXIT_FAILURE)
	{
		msg = ft_strjoin("Could not export variable: ", shell->parms[1]);
		msg = ft_strjoin(msg, "\n");
		ft_error(shell, msg, 0);
		free(msg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
