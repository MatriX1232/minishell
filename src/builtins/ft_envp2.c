/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:57:32 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/17 12:11:26 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

void	ft_free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
	env = NULL;
}

bool	ft_check_validity(t_minishell *shell, char *var)
{
	int		i;
	char	**split;

	if (var && *var == '=')
		return (ft_add_var(shell, "?=1", 1), false);
	split = ft_split(var, '=');
	if (!split)
		return (ft_error(shell, E_SPLIT, 1), false);
	if (ft_tablen(split) != 2)
		return (ft_free_env(split), false);
	i = 0;
	while (split[0][i] && (ft_isalnum(split[0][i]) || split[0][i] == '_'))
		i++;
	if (split[0][i] != '\0')
	{
		ft_add_var(shell, "?=1", 1);
		return (ft_free_env(split), false);
	}
	return (ft_free_env(split), true);
}

int	ft_tablen(char **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

char	**ft_init_env(char **envp)
{
	int		i;
	char	**new;

	i = 0;
	new = (char **) malloc((ft_tablen(envp) + 2) * sizeof(char *));
	if (!new)
		return (ft_error(NULL, E_MALLOC, 0), NULL);
	while (envp[i])
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	new[i++] = ft_strdup("?=0");
	new[i] = NULL;
	return (new);
}
