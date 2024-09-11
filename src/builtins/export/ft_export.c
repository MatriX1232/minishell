/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idomagal <idomagal@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 23:01:30 by msolinsk          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/11 13:27:06 by idomagal         ###   ########.fr       */
=======
/*   Updated: 2024/09/11 14:53:45 by msolinsk         ###   ########.fr       */
>>>>>>> c7f9780 (Fixed export and unset)
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../builtins.h"

static void	ft_print_parms(char **parms)
{
	int	i;

	i = 0;
	while (parms[i])
		printf("%s\n", parms[i++]);
}

int	ft_export(t_minishell *shell)
{
	char	*msg;

	if (!shell->parms[1])
		ft_print_parms(shell->env);
	else if (!shell->parms[1] || shell->parms[0][6] != '\0')
	{
		msg = ft_strdup("Usage: export <variable> | <variable> is optional\n");
		ft_error(shell, msg, 0);
		free(msg);
		return (EXIT_FAILURE);
	}
	else if (ft_add_var(shell, shell->parms[1]) == EXIT_FAILURE)
	{
		msg = ft_strjoin("Could not export variable: ", shell->parms[1]);
		ft_error(shell, msg, 0);
		free(msg);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
