/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:49:30 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/07 21:12:25 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//	Free the shell structure
void	ft_free_shell(t_minishell *shell)
{
	free(shell->cwd);
	free(shell->print_prefix_success);
	free(shell->print_prefix_failure);
	free(shell->parms);
	free(shell);
}
