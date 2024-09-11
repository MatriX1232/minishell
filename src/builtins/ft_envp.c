/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:35:52 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/11 15:59:51 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../include/minishell.h"

static int	ft_tablen(char **tab)
{
	int	len;

	len = 0;
	while (tab[len])
		len++;
	return (len);
}

static void	ft_free_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		free(env[i++]);
	free(env);
	env = NULL;
}

// Function to find if the variable exists in env
bool	ft_exists_var(t_minishell *shell, char *var_name)
{
	int		i;
	char	**env;

	i = 0;
	env = shell->env;
	while (env[i])
	{
		if (ft_strncmp(env[i], var_name, ft_strlen(var_name)) == 0)
			return (true);
		i++;
	}
	return (false);
}

int	ft_add_var(t_minishell *shell, char *var)
{
	int		i;
	int		len;
	char	**new_env;

	len = ft_tablen(shell->env);
	new_env = (char **) malloc((len + 2) * sizeof(char *));
	if (!new_env)
		return (ft_error(shell, "Could not allocate memory for new_env\n", 1), EXIT_FAILURE);
	i = 0;
	while (shell->env[i])
	{
		new_env[i] = shell->env[i];
		i++;
	}
	new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
	// ft_free_env(shell->env);
	(void)ft_free_env;
	shell->env = new_env;
	return (EXIT_SUCCESS);
}

int	ft_delete_var(t_minishell *shell, char *var)
{
	int		i;
	int		j;
	int		len;
	char	**new_env;
	char	**split;

	len = ft_tablen(shell->env);
	i = 0;
	j = 0;
	new_env = (char **) malloc(len * sizeof(char *));
	if (!new_env)
		return (ft_error(shell, "Could not allocate memory for new_env\n", 1), EXIT_FAILURE);
	while (i < len)
	{
		split = ft_split(shell->env[i], '='); // split[0] is the variable name
		if (ft_strncmp(split[0], var, ft_strlen(var)) == 0)
		{
			i++;
			continue ;
		}
		new_env[j++] = shell->env[i++];
	}
	new_env[i] = NULL;
	shell->env = new_env;
	return (EXIT_SUCCESS);
}
