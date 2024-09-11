/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:41:31 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/11 13:03:18 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libraries.h"
#include "../include/structures.h"

/*
	Takes whole string and returns pointer to inside string

	Success:
		Returns pointer to string contained within the bigger one

	Fail:	(exp. when there isn't dequote)
		Returns NULL
*/
char	*ft_qparser(char *str)
{
	char	*qstart;
	char	*qend;
	char	*new;

	qstart = ft_strchr(str, '\34');
	qend = ft_strrchr(str, '\34');

	if (!qstart || !qend || qstart == qend)
		return (NULL);
	new = ft_substr(str, qstart - str, qend - qstart);
	return (new);
}

void	ft_qparser_shell(t_minishell *shell, char *str)
{
	char	*qstart;
	char	*qend;
	char	*new;

	qstart = ft_strchr(str, '"');
	qend = ft_strrchr(str, '"');

	if (!qstart || !qend || qstart == qend)
	{
		shell->parms = ft_split(str, ' ');
		shell->quotes = false;
	}
	else
	{
		new = ft_substr(str, qstart - str + 1, qend - qstart - 1);
		shell->parms = (char **) malloc(2 * sizeof(char *));
		if (!shell->parms)
			return ft_error(shell, "Could not allocate memory for shell->parms\n", 1);
		shell->parms[1] = new;
		shell->parms[0] = ft_substr(str, 0, ft_strchr(str, ' ') - str);
		shell->quotes = true;
	}
}
