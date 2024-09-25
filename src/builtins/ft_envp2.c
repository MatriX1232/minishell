/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 13:57:32 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/25 16:39:13 by msolinsk         ###   ########.fr       */
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
	// env = NULL;
}

bool	ft_check_validity(t_minishell *shell, char *var)
{
	char	**split;

	split = ft_split(var, '=');
	if (!split)
		return (ft_error(shell, "Couldn't split var\n", 1), false);
	if (ft_tablen(split) == 2)
	{
		ft_free_env(split);
		return (true);
	}
	ft_free_env(split);
	return (false);
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
	new = (char **) malloc((ft_tablen(envp) + 1) * sizeof(char *));
	if (!new)
		return (ft_error(NULL, "Cannot allocate memory\n", 0), NULL);
	while (envp[i])
	{
		new[i] = ft_strdup(envp[i]);
		i++;
	}
	new[i] = NULL;
	return (new);
}
