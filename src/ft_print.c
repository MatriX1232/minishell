/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:05:58 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/07 21:12:43 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

//	Print error message on stderr
void	ft_error(t_minishell *shell, char *message)
{
	perror(RED);
	if (shell)
		perror(shell->print_prefix_failure);
	perror(message);
	perror(END);
}
