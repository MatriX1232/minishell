/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:34:12 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/07 22:21:27 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../builtins.h"

//	Print the current working directory
int	ft_pwd(t_minishell *shell)
{
	getcwd(shell->cwd, 1024);
	if (!shell->cwd)
	{
		perror("Could not get current working directory\n");
		return (EXIT_FAILURE);
	}
	printf("%s\n", shell->cwd);
	return (EXIT_SUCCESS);
}
