/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:35:52 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/21 14:02:00 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../../include/minishell.h"

// Function to find if the variable exists in env
int	ft_add_exists_var(t_minishell *shell, char *var)
{
	int		i;
	char	*var_name;
	char	**split;

	split = ft_split(var, '=');
	if (!split)
		return (ft_error(shell, "Couldn't split var\n", 1), EXIT_FAILURE);
	var_name = split[0];
	free(split);
	i = 0;
	while (shell->env[i])
	{
		if (ft_strncmp(shell->env[i], var_name, ft_strlen(var_name)) == 0)
		{
			free(shell->env[i]);
			shell->env[i] = ft_strdup(var);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	return (EXIT_FAILURE);
}

int	ft_add_var(t_minishell *shell, char *var)
{
	int		i;
	int		len;
	char	**new_env;

	if (ft_check_validity(shell, var) == false)
		return (ft_error(shell, "Argument is not valid\n", 0), EXIT_FAILURE);
	if (ft_add_exists_var(shell, var) == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	len = ft_tablen(shell->env);
	new_env = (char **) malloc((len + 2) * sizeof(char *));
	if (!new_env)
		return (ft_error(shell, "Couldn't allocate memory\n", 1), EXIT_FAILURE);
	i = 0;
	while (shell->env[i])
	{
		new_env[i] = shell->env[i];
		i++;
	}
	new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
	shell->env = new_env;
	return (EXIT_SUCCESS);
}

static int	ft_cleanup_delete(t_minishell *shell, char **new_env, int i, int j)
{
	new_env[i] = NULL;
	shell->env = new_env;
	if (i == j)
		return (EXIT_FAILURE);
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
		return (ft_error(shell, "Couldn't allocate memory\n", 1), EXIT_FAILURE);
	while (i < len)
	{
		split = ft_split(shell->env[i], '=');
		if (ft_strncmp(split[0], var, ft_strlen(var)) == 0)
		{
			i++;
			continue ;
		}
		new_env[j++] = shell->env[i++];
	}
	return (ft_cleanup_delete(shell, new_env, i, j));
}
