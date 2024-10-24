/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_anim.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 15:41:26 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/23 01:57:12 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/*
	THIS IS EASTER EGG FOR SEG FAULT, TERMINATION AND ABORT SIGNALS
*/

char	**ft_init_ship(char **ship)
{
	ship = (char **) malloc(13 * sizeof(char *));
	if (!ship)
	{
		ft_error(NULL, "Even ship failed wtf bro\n", 1);
		exit(EXIT_FAILURE);
	}
	ship[0] = ft_strdup("⠀⠀⠀⠀⣤⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	ship[1] = ft_strdup("⠀⠀⠀⠀⣿⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀\n");
	ship[2] = ft_strdup("⠀⠀⠀⠀⣿⣿⠻⣿⣦⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⠀⠀⠀\n");
	ship[3] = ft_strdup("⠀⠀⠀⢀⣿⣿⠀⠈⠻⣿⣦⡀⠀⠀⢀⣴⣿⣦⡀⠀⠀⣠⣾⡿⠋⠀⠀⠀\n");
	ship[4] = ft_strdup("⠀⠀⠀⣾⣿⣿⣷⣄⠀⠈⠻⣿⣦⣴⣿⠟⠉⠻⣿⣦⣾⡿⠋⠀⠀⣠⣾⡿\n");
	ship[5] = ft_strdup("⠀⠀⠀⢿⣿⣿⣿⣿⣷⣄⠀⠈⠻⣿⣧⣄⠀⢠⡌⠻⣿⣦⡀⣠⣾⡿⠋⠀\n");
	ship[6] = ft_strdup("⠀⠀⠀⠈⠻⣿⣿⣿⣿⣿⣿⣦⡀⠈⠹⢿⣷⣌⠁⢠⡌⠻⣿⣿⡋⠀⠀⠀\n");
	ship[7] = ft_strdup("⠀⠀⠀⠀⠀⠈⠻⣿⣿⣿⣿⣿⣿⣦⡀⠈⠙⣿⣷⣄⠀⢠⡌⠻⣿⣦⡀⠀\n");
	ship[8] = ft_strdup("⠀⠀⠀⠀⠀⠀⠀⠈⠻⣿⣿⣿⣿⣿⣿⣦⡀⠀⠛⢿⣷⣄⠀⣤⠈⠻⣿⣦\n");
	ship[9] = ft_strdup("⠀⠀⠀⣀⡀⠀⠀⠀⢀⡈⠻⣿⡿⢛⡛⠿⠿⠀⢀⡀⠙⢿⠇⢀⣀⠀⠈⠉\n");
	ship[10] = ft_strdup("⢠⣶⣶⣿⣷⣶⣶⣶⣿⣿⣶⣶⣶⣿⣿⣶⣶⣶⣿⣿⣶⣶⣶⣾⣿⣶⣶⡄\n");
	ship[11] = ft_strdup("⠈⠋⠉⠀⠈⠉⠋⠉⠁⠈⠉⠛⠉⠁⠈⠉⠛⠉⠁⠈⠉⠙⠉⠁⠀⠉⠙⠁\n");
	ship[12] = NULL;
	return (ship);
}

static void	ft_delete_last_n_lines(int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		printf("\033[A");
		printf("\033[K");
		i++;
	}
}

static void	ft_clear_and_wait(int wait_time)
{
	usleep(wait_time * 1000);
	ft_delete_last_n_lines(12);
}

void	ft_animate_ship(void)
{
	int		i;
	int		j;
	int		iter;
	int		anim_speed;
	char	**ship;

	ship = NULL;
	ship = ft_init_ship(ship);
	anim_speed = 400;
	printf("%s", RED);
	iter = 0;
	while (iter < 10)
	{
		j = -1;
		while (++j < iter)
			printf("\n");
		i = 0;
		while (i < 12 - 2 - iter)
			printf("%s", ship[i++]);
		printf("%s", ship[10]);
		printf("%s", ship[11]);
		ft_clear_and_wait(anim_speed);
		iter++;
	}
	ft_free_env(ship);
}
