/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/11 13:35:52 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/18 17:21:50 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"
#include "../../include/minishell.h"

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

static bool	ft_check_validity(t_minishell *shell, char *var)
{
	char	**split;

	split = ft_split(var, '=');
	if (!split)
		return (ft_error(shell, "Couldn't split var\n", 1), false);
	if (ft_tablen(split) == 2)
	{
		free(split);
		return (true);
	}
	return (false);
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
		return (ft_error(shell, "Could not allocate memory for new_env\n", 1), EXIT_FAILURE);
	i = 0;
	while (shell->env[i])
	{
		new_env[i] = shell->env[i];
		i++;
	}
	new_env[i] = ft_strdup(var);
	new_env[i + 1] = NULL;
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
	if (i == j)
		return (EXIT_FAILURE); 	// It means that there is no VAS with that name
	return (EXIT_SUCCESS);
}
