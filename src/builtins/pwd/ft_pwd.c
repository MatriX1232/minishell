/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:34:12 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/30 11:44:07 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../builtins.h"

//	Print the current working directory
int	ft_pwd(t_minishell *shell)
{
	char	*msg;

	getcwd(shell->cwd, 1024);
	if (!shell->cwd)
	{
		msg = ft_strdup("Could not get current working directory\n");
		ft_error(shell, msg, 0);
		free(msg);
		ft_add_var(shell, "?=1", 1);
		return (EXIT_FAILURE);
	}
	ft_putstr_fd(shell->cwd, STDOUT_FILENO);
	ft_putstr_fd("\n", STDOUT_FILENO);
	ft_add_var(shell, "?=0", 1);
	return (EXIT_SUCCESS);
}
