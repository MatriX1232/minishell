/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_parser3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 13:17:48 by idomagal          #+#    #+#             */
/*   Updated: 2024/10/23 14:06:52 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "quotes/quotes.h"

void	ft_redirection(char *str, char *ret, int *i)
{
	ft_strcat_char(ret, SPLIT_SEP);
	if ((str[*i] == '>' && str[*i + 1] == '>') \
		|| (str[*i] == '<' && str[*i + 1] == '<'))
	{
		ft_strncat(ret, &str[*i], 2);
		*i += 2;
	}
	else
	{
		ft_strncat(ret, &str[*i], 1);
		(*i)++;
	}
	ft_strcat_char(ret, SPLIT_SEP);
}

void	ft_strcat_char(char *dest, char c)
{
	int	len;

	len = ft_strlen(dest);
	dest[len] = c;
	dest[len + 1] = '\0';
}

char	*ft_strncat(char *dest, const char *src, int n)
{
	int	i;
	int	dest_len;

	i = 0;
	dest_len = ft_strlen(dest);
	while (src[i] && i < n)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';
	return (dest);
}

void	ft_normal(char *str, char *ret, int *i)
{
	int	len;

	len = ft_strlen(ret);
	ret[len] = str[*i];
	ret[len + 1] = '\0';
	(*i)++;
}
