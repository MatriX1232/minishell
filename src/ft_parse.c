/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 22:07:17 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/08 14:18:02 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/structures.h"
#include "../include/libraries.h"

int	ft_parse(t_minishell *shell, char *line)
{
	char	*msg;

	if (ft_strncmp(line, "pwd", 3) == 0)
		return (ft_pwd(shell));
	else if (ft_strncmp(line, "echo", 4) == 0)
		return (ft_echo(shell));
	else if (ft_strncmp(line, "cd", 2) == 0)
		return (ft_cd(shell, line));
	else
	{
		msg = ft_strjoin("Command not found: ", line);
		return (ft_error(shell, msg), free(msg), EXIT_FAILURE);
	}
}
