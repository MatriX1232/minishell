/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 22:36:29 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/16 22:10:52 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../builtins.h"
#include "../../../include/minishell.h"

int	ft_echo(t_minishell *shell)
{
	int		i;
	int		len;
	bool	f_raw;

	i = 1;
	len = ft_tablen(shell->parms);
	if (shell->parms[1] && ft_strncmp(shell->parms[1], "-n", 3) == 0)
		i = 2;
	f_raw = false;
	if (shell->raw_parsed != NULL)
		printf("%s", shell->raw_parsed);
	if (shell->raw_parsed != NULL)
		f_raw = true;
	while (shell->parms[i] && !f_raw)
	{
		printf("%s", shell->parms[i]);
		if (i < len)
			printf(" ");
		i++;
	}
	if (shell->parms[1] && ft_strncmp(shell->parms[1], "-n", 3) != 0)
		printf("\n");
	else if (!shell->parms[1])
		printf("\n");
	return (ft_add_var(shell, "?=0", 1), EXIT_SUCCESS);
}
