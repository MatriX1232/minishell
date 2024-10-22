/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:08:41 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/23 01:46:57 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include "../include/minishell.h"

static char	*ft_get_top(char *title, int width, char *tc, char *bc)
{
	int		i;
	int		cc;
	int		size;
	char	*top;

	size = (width * 4);
	top = ft_calloc((size + 1), sizeof(char));
	if (!top)
		return (NULL);
	i = 0;
	ft_strlcat(top, bc, size + 1);
	i = ft_strlcat(top, "╭─ ", size + 1);
	ft_strlcat(top, tc, size + 1);
	i = ft_strlcat(top, title, size + 1);
	cc = 4 + ft_strlen(title);
	top[i++] = ' ';
	ft_strlcat(top, bc, size + 1);
	while (cc < width)
	{
		i = ft_strlcat(top, "─", i + 4);
		cc++;
	}
	i = ft_strlcat(top, "╮\n", i + 6);
	return top;
}

static char	*ft_get_content(char *content, int width_ref, char *cc, char *bc)
{
	int		i;
	int		j;
	int		len;
	char	*sub;
	char	*ret;

	ret = ft_calloc(2000, sizeof(char));
	if (!ret)
		return (NULL);
	i = 0;
	len = ft_strlen(content);
	while (i < len)
	{
		ft_strlcat(ret, bc, 2000);
		ft_strlcat(ret, "│ ", 2000);
		ft_strlcat(ret, cc, 2000);
		sub = ft_substr(content, i, i + width_ref - 4);
		// printf("i: %d | sub: <<%s>>\n", i, sub);
		j = ft_strlcat(ret, sub, 2000);
		while (j < width_ref + 10)
			ret[j++] = ' ';
		ft_strlcat(ret, bc, 2000);
		ft_strlcat(ret, " │\n", 2000);
		i += ft_strlen(sub) + 1;
		free(sub);
	}
	return (ret);
}

static char	*ft_get_bottom(int width)
{
	int		i;
	char	*ret;

	ret = ft_calloc(((width * 4) + 1), sizeof(char));
	if (!ret)
		return (NULL);
	ft_strlcat(ret, "╰─", 2000);
	i = -1;
	while (++i < width - 4)
		ft_strlcat(ret, "─", 2000);
	ft_strlcat(ret, "─╯\n", 2000);
	return (ret);
}

/*
	TC = Title color
	CC = Content color
	BC = Border color
*/
void	outline(char *title, char *content, char *tc, char *cc, char *bc)
{
	struct winsize	w;
	char			*ret;

	(void)tc;
	(void)cc;
	(void)bc;

	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
	ret = ft_get_top(title, w.ws_col, tc, bc);
	printf("%s", ret);
	free(ret);
	ret = ft_get_content(content, w.ws_col, cc, bc);
	printf("%s", ret);
	free(ret);
	ret = ft_get_bottom(w.ws_col);
	printf("%s", ret);
	free(ret);
}
