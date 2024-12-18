/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:49:30 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/17 13:22:52 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//	Free the shell structure
void	ft_free_shell(t_minishell *shell)
{
	if (shell->cwd)
		free(shell->cwd);
	if (shell->print_prefix_success)
		free(shell->print_prefix_success);
	if (shell->print_prefix_failure)
		free(shell->print_prefix_failure);
	if (shell->parms != NULL)
		ft_free_parms(shell);
	if (shell->env != NULL)
		ft_free_env(shell->env);
	free(shell);
}

//	Free the parameters in form of a char**
void	ft_free_parms(t_minishell *shell)
{
	int	i;

	i = 0;
	while (shell->parms[i])
	{
		free(shell->parms[i]);
		i++;
	}
	free(shell->parms);
	shell->parms = NULL;
}
