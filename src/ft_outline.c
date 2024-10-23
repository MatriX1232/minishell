/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:08:41 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/23 10:45:58 by msolinsk         ###   ########.fr       */
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

static char	*ft_get_content(char *content, char *cc, char *bc, int longest)
{
	int		i;
	int		j;
	char	*ret;
	char	**split;

	i = 0;
	ret = ft_calloc(20000, sizeof(char));
	if (!ret)
		return (NULL);
	split = ft_split(content, '\n');
	while (split[i])
	{
		ft_strlcat(ret, bc, 2000);
		ft_strlcat(ret, "│ ", 2000);
		ft_strlcat(ret, cc, 2000);
		ft_strlcat(ret, split[i], 2000);
		j = (int)ft_strlen(split[i]);
		while (j < longest)
		{
			ft_strlcat(ret, " ", 2000);
			j++;
		}
		ft_strlcat(ret, bc, 2000);
		ft_strlcat(ret, " │\n", 20000);
		i++;
	}
	ft_free_env(split);
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

static int	ft_get_longest_width(char *content)
{
	int		i;
	int		longest;
	char	**split;

	i = 0;
	longest = 0;
	split = ft_split(content, '\n');
	while (split[i])
	{
		if ((int)ft_strlen(split[i]) > longest)
			longest = ft_strlen(split[i]);
		i++;
	}
	ft_free_env(split);
	return (longest);
}

/*
	TC = Title color
	CC = Content color
	BC = Border color
*/
void	outline(char *title, char *content, char *tc, char *cc, char *bc)
{
	int				longest;
	char			*ret;

	longest = ft_get_longest_width(content);
	ret = ft_get_top(title, longest + 4, tc, bc);
	printf("%s", ret);
	free(ret);
	ret = ft_get_content(content, cc, bc, longest);
	printf("%s", ret);
	free(ret);
	ret = ft_get_bottom(longest + 4);
	printf("%s", ret);
	free(ret);
}
