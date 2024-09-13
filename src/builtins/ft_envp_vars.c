/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_envp_vars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 14:16:25 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/13 12:10:17 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "builtins.h"

static void	ft_free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free(split);
}

/*
	If SUCCESS:
		Returns the value of the variable

	If FAILURE:
		Returns NULL
*/
char	*ft_get_var_value(t_minishell *shell, char *var)
{
	int		i;
	char	**split;

	i = 0;
	while (shell->env[i])
	{
		split = ft_split(shell->env[i], '='); // split[0] is the variable name
		if (ft_strncmp(split[0], var, ft_strlen(split[0])) == 0)
			return (split[1]);
		ft_free_split(split);
		i++;
	}
	return (NULL);
}

