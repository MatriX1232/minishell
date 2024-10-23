/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 20:05:58 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/23 19:11:15 by msolinsk         ###   ########.fr       */
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

int	ft_check_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\t')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_malloc_ret(t_minishell *shell, int *i)
{
	char	*ret;

	ret = (char *)ft_calloc(10000, sizeof(char));
	if (!ret)
	{
		ft_error(shell, "Could not calloc\n", 1);
		return (NULL);
	}
	*i = 0;
	return (ret);
}
