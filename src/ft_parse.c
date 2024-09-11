/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 22:07:17 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/08 23:38:49 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/structures.h"
#include "../include/libraries.h"

int	ft_parse(t_minishell *shell, char *line)
{
	char	*msg;

	if (*line == '\0')
		return (EXIT_SUCCESS);
	else if (ft_strncmp(line, "pwd", 4) == 0)
		return (ft_pwd(shell));
	else if (ft_strncmp(line, "echo", 4) == 0)
		return (ft_echo(shell));
	else if (ft_strncmp(line, "cd", 2) == 0)
		return (ft_cd(shell));
	else if (ft_strncmp(line, "env", 4) == 0)
		return (ft_env(shell));
	else if (ft_strncmp(line, "unset", 5) == 0)
		return (ft_unset(shell));
	else if (ft_strncmp(line, "export", 6) == 0)
		return (ft_export(shell));
	else
	{
		msg = ft_strjoin("Command not found: ", line);
		return (ft_error(shell, msg, 0), ft_putchar_fd('\n', 2), free(msg), EXIT_FAILURE);
	}
}
