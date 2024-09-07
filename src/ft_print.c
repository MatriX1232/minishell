/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:05:58 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/07 22:28:22 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//	Print error message on stderr
void	ft_error(t_minishell *shell, char *message)
{
	ft_putstr_fd(RED, 2);
	if (shell)
		ft_putstr_fd(shell->print_prefix_failure, 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(END, 2);
}
