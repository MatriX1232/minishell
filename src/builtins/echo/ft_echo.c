/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 22:36:29 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/22 13:07:27 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"
#include "../../../include/minishell.h"

int	ft_echo(t_minishell *shell, char **argv)
{
	int		i;
	int		len;

	i = 1;
	len = ft_tablen(argv);
	if (argv[1] && ft_strncmp(argv[1], "-n", 3) == 0)
		i = 2;
	while (argv[i])
	{
		ft_putstr_fd(argv[i], STDOUT_FILENO);
		if (i < len - 1)
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (argv[1] && ft_strncmp(argv[1], "-n", 3) != 0)
		ft_putstr_fd("\n", STDOUT_FILENO);
	else if (!argv[1])
		ft_putstr_fd("\n", STDOUT_FILENO);
	return (ft_add_var(shell, "?=0", 1), EXIT_SUCCESS);
}
