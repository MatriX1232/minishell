/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/10 11:10:34 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/23 15:03:40 by msolinsk         ###   ########.fr       */
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

static void	ft_delete_last_n_lines(int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("\033[A");
		printf("\033[K");
	}
}

static void	ft_animate_ship(void)
{
	int	anim_speed = 700;

	printf("%s", RED);
	printf("⠀⠀⠀⠀⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⣿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⣿⣿⠻⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⠀⠀⠀\n");
	printf("⠀⠀⠀⢀⣿⣿⠀⠈⠻⣿⣦⡀⠀⠀⢀⣴⣿⣦⡀⠀⠀⣠⣾⡿⠋⠀⠀⠀\n");
	printf("⠀⠀⠀⣾⣿⣿⣷⣄⠀⠈⠻⣿⣦⣴⣿⠟⠉⠻⣿⣦⣾⡿⠋⠀⠀⣠⣾⡿\n");
	printf("⠀⠀⠀⢿⣿⣿⣿⣿⣷⣄⠀⠈⠻⣿⣧⣄⠀⢠⡌⠻⣿⣦⡀⣠⣾⡿⠋⠀\n");
	printf("⠀⠀⠀⠈⠻⣿⣿⣿⣿⣿⣿⣦⡀⠈⠹⢿⣷⣌⠁⢠⡌⠻⣿⣿⡋⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠈⠻⣿⣿⣿⣿⣿⣿⣦⡀⠈⠙⣿⣷⣄⠀⢠⡌⠻⣿⣦⡀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠈⠻⣿⣿⣿⣿⣿⣿⣦⡀⠀⠛⢿⣷⣄⠀⣤⠈⠻⣿⣦\n");
	printf("⠀⠀⠀⣀⡀⠀⠀⠀⢀⡈⠻⣿⡿⢛⡛⠿⠿⠀⢀⡀⠙⢿⠇⢀⣀⠀⠈⠉\n");
	printf("⢠⣶⣶⣿⣷⣶⣶⣶⣿⣿⣶⣶⣶⣿⣿⣶⣶⣶⣿⣿⣶⣶⣶⣾⣿⣶⣶⡄\n");
	printf("⠈⠋⠉⠀⠈⠉⠋⠉⠁⠈⠉⠛⠉⠁⠈⠉⠛⠉⠁⠈⠉⠙⠉⠁⠀⠉⠙⠁\n");
	usleep(anim_speed * 1000);
	ft_delete_last_n_lines(12);
	printf("\n\n");
	printf("⠀⠀⠀⠀⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⣿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⣿⣿⠻⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⠀⠀⠀\n");
	printf("⠀⠀⠀⢀⣿⣿⠀⠈⠻⣿⣦⡀⠀⠀⢀⣴⣿⣦⡀⠀⠀⣠⣾⡿⠋⠀⠀⠀\n");
	printf("⠀⠀⠀⣾⣿⣿⣷⣄⠀⠈⠻⣿⣦⣴⣿⠟⠉⠻⣿⣦⣾⡿⠋⠀⠀⣠⣾⡿\n");
	printf("⠀⠀⠀⢿⣿⣿⣿⣿⣷⣄⠀⠈⠻⣿⣧⣄⠀⢠⡌⠻⣿⣦⡀⣠⣾⡿⠋⠀\n");
	printf("⠀⠀⠀⠈⠻⣿⣿⣿⣿⣿⣿⣦⡀⠈⠹⢿⣷⣌⠁⢠⡌⠻⣿⣿⡋⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠈⠻⣿⣿⣿⣿⣿⣿⣦⡀⠈⠙⣿⣷⣄⠀⢠⡌⠻⣿⣦⡀⠀\n");
	printf("⢠⣶⣶⣿⣷⣶⣶⣶⣿⣿⣶⣶⣶⣿⣿⣶⣶⣶⣿⣿⣶⣶⣶⣾⣿⣶⣶⡄\n");
	printf("⠈⠋⠉⠀⠈⠉⠋⠉⠁⠈⠉⠛⠉⠁⠈⠉⠛⠉⠁⠈⠉⠙⠉⠁⠀⠉⠙⠁\n");
	usleep(anim_speed * 1000);
	ft_delete_last_n_lines(12);
	printf("\n\n\n\n");
	printf("⠀⠀⠀⠀⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⣿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⣿⣿⠻⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⠀⠀⠀\n");
	printf("⠀⠀⠀⢀⣿⣿⠀⠈⠻⣿⣦⡀⠀⠀⢀⣴⣿⣦⡀⠀⠀⣠⣾⡿⠋⠀⠀⠀\n");
	printf("⠀⠀⠀⣾⣿⣿⣷⣄⠀⠈⠻⣿⣦⣴⣿⠟⠉⠻⣿⣦⣾⡿⠋⠀⠀⣠⣾⡿\n");
	printf("⠀⠀⠀⢿⣿⣿⣿⣿⣷⣄⠀⠈⠻⣿⣧⣄⠀⢠⡌⠻⣿⣦⡀⣠⣾⡿⠋⠀\n");
	printf("⢠⣶⣶⣿⣷⣶⣶⣶⣿⣿⣶⣶⣶⣿⣿⣶⣶⣶⣿⣿⣶⣶⣶⣾⣿⣶⣶⡄\n");
	printf("⠈⠋⠉⠀⠈⠉⠋⠉⠁⠈⠉⠛⠉⠁⠈⠉⠛⠉⠁⠈⠉⠙⠉⠁⠀⠉⠙⠁\n");
	usleep(anim_speed * 1000);
	ft_delete_last_n_lines(12);
	printf("\n\n\n\n\n\n");
	printf("⠀⠀⠀⠀⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⣿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⣿⣿⠻⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⠀⠀⠀\n");
	printf("⠀⠀⠀⢀⣿⣿⠀⠈⠻⣿⣦⡀⠀⠀⢀⣴⣿⣦⡀⠀⠀⣠⣾⡿⠋⠀⠀⠀\n");
	printf("⢠⣶⣶⣿⣷⣶⣶⣶⣿⣿⣶⣶⣶⣿⣿⣶⣶⣶⣿⣿⣶⣶⣶⣾⣿⣶⣶⡄\n");
	printf("⠈⠋⠉⠀⠈⠉⠋⠉⠁⠈⠉⠛⠉⠁⠈⠉⠛⠉⠁⠈⠉⠙⠉⠁⠀⠉⠙⠁\n");
	usleep(anim_speed * 1000);
	ft_delete_last_n_lines(12);
	printf("\n\n\n\n\n\n\n\n\n");
	printf("⠀⠀⠀⠀⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⢠⣶⣶⣿⣷⣶⣶⣶⣿⣿⣶⣶⣶⣿⣿⣶⣶⣶⣿⣿⣶⣶⣶⣾⣿⣶⣶⡄\n");
	printf("⠈⠋⠉⠀⠈⠉⠋⠉⠁⠈⠉⠛⠉⠁⠈⠉⠛⠉⠁⠈⠉⠙⠉⠁⠀⠉⠙⠁\n");
	ft_delete_last_n_lines(12);
	usleep(anim_speed * 1000);
	printf("⠀⠀⠀⠀⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⣿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⣿⣿⠻⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⠀⠀⠀\n");
	printf("⠀⠀⠀⢀⣿⣿⠀⠈⠻⣿⣦⡀⠀⠀⢀⣴⣿⣦⡀⠀⠀⣠⣾⡿⠋⠀⠀⠀\n");
	printf("⠀⠀⠀⣾⣿⣿⣷⣄⠀⠈⠻⣿⣦⣴⣿⠟⠉⠻⣿⣦⣾⡿⠋⠀⠀⣠⣾⡿\n");
	printf("⠀⠀⠀⢿⣿⣿⣿⣿⣷⣄⠀⠈⠻⣿⣧⣄⠀⢠⡌⠻⣿⣦⡀⣠⣾⡿⠋⠀\n");
	printf("⠀⠀⠀⠈⠻⣿⣿⣿⣿⣿⣿⣦⡀⠈⠹⢿⣷⣌⠁⢠⡌⠻⣿⣿⡋⠀⠀⠀\n");
	printf("⠀⠀⠀⠀⠀⠈⠻⣿⣿⣿⣿⣿⣿⣦⡀⠈⠙⣿⣷⣄⠀⢠⡌⠻⣿⣦⡀⠀\n");
	printf("⠀⠀⠀⠀⠀⠀⠀⠈⠻⣿⣿⣿⣿⣿⣿⣦⡀⠀⠛⢿⣷⣄⠀⣤⠈⠻⣿⣦\n");
	printf("⠀⠀⠀⣀⡀⠀⠀⠀⢀⡈⠻⣿⡿⢛⡛⠿⠿⠀⢀⡀⠙⢿⠇⢀⣀⠀⠈⠉\n");
	printf("⢠⣶⣶⣿⣷⣶⣶⣶⣿⣿⣶⣶⣶⣿⣿⣶⣶⣶⣿⣿⣶⣶⣶⣾⣿⣶⣶⡄\n");
	printf("⠈⠋⠉⠀⠈⠉⠋⠉⠁⠈⠉⠛⠉⠁⠈⠉⠛⠉⠁⠈⠉⠙⠉⠁⠀⠉⠙⠁\n");
}

void	sig_abort(int sig)
{
	(void)sig;
	ft_animate_ship();
	printf("▶ ABORT %s\n", END);
	exit(EXIT_FAILURE);
}
