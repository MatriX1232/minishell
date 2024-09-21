/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:05:58 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/21 14:25:14 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//	Print error message on stderr
void	ft_error(t_minishell *shell, char *message, int shell_failure)
{
	ft_putstr_fd(RED, 2);
	if (shell)
		ft_putstr_fd(shell->print_prefix_failure, 2);
	if (shell_failure)
		ft_free_shell(shell);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(END, 2);
}
