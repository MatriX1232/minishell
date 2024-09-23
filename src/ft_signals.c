/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:10:34 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/23 12:55:07 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/structures.h"
#include "../include/libraries.h"

void	sig_ctrlc(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sig_term(int sig)
{
	(void)sig;
	printf("%sX﹏X  ▶ TERMINATED MINISHELL %s\n", RED, END);
}

void	sig_segv(int sig)
{
	(void)sig;
	printf("%s( -_•)▄︻テحكـ━一💥  ▶ SEGMENTATION FAULT %s\n", RED, END);
	exit(EXIT_FAILURE);
}
