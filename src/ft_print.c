/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:05:58 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/08 22:39:49 by msolinsk         ###   ########.fr       */
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

//	Print command success message on stdout
void	ft_success(t_minishell *shell)
{
	write(1, YELLOW, ft_strlen(YELLOW));
	if (shell)
		write(1, shell->print_prefix_success, ft_strlen(shell->print_prefix_success));
	else
		ft_error(shell, "Could not print success message\n", 0);
	write(1, END, ft_strlen(END));
}
