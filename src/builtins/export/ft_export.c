/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 23:01:30 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/30 11:47:11 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../builtins.h"
#include "../../quotes/quotes.h"

static void	ft_chose_exit_val(t_minishell *shell, char *var)
{
	int	i;

	i = 0;
	while (var[i] && (ft_isalnum(var[i]) || var[i] == '_'))
		i++;
	if (var[i] == '\0' && !ft_intab('=', var))
		ft_add_var(shell, "?=0", 1);
	else if (var[i] != '\0' && !ft_intab('=', var))
		ft_add_var(shell, "?=1", 1);
	i = 0;
	while (var[i] && var[i] >= '0' && var[i] <= '9')
		i++;
	if (var[i] == '\0')
		ft_add_var(shell, "?=1", 1);
}

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

static int	ft_usage(t_minishell *shell)
{
	ft_add_var(shell, "?=0", 0);
	ft_chose_exit_val(shell, shell->parms[1]);
	return (EXIT_FAILURE);
}

static int	ft_export_error(t_minishell *shell)
{
	char	*msg;

	if (shell->parms[1][ft_strlen(shell->parms[1]) - 1] == '=')
	{
		ft_add_var(shell, "?=0", 1);
		return (EXIT_FAILURE);
	}
	msg = ft_strjoin("Could not export variable: ", shell->parms[1]);
	msg = ft_strjoin_free(msg, "\n", 1, 0);
	ft_error(shell, msg, 0);
	free(msg);
	ft_add_var(shell, "?=1", 1);
	return (EXIT_FAILURE);
}

int	ft_export(t_minishell *shell)
{
	int	i;

	if (!shell->parms[1])
		ft_print_parms(shell->env);
	i = 1;
	while (shell->parms[i])
	{
		if (shell->parms[i] && ft_strchr(shell->parms[i], '=') == NULL)
			return (ft_usage(shell));
		else if (ft_add_var(shell, shell->parms[i], 0) == EXIT_FAILURE)
			return (ft_export_error(shell));
		i++;
	}
	return (EXIT_SUCCESS);
}
