/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_outline.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 00:08:41 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/23 11:11:48 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/ioctl.h>
#include "../include/minishell.h"

static char	*ft_get_top(char *title, int width, char *tc, char *cc)
{
	int		i;
	int		c_count;
	int		size;
	char	*top;

	size = (width * 4);
	top = ft_calloc((size + 1), sizeof(char));
	if (!top)
		return (NULL);
	i = 0;
	ft_strlcat(top, cc, size + 1);
	i = ft_strlcat(top, "╭─ ", size + 1);
	ft_strlcat(top, tc, size + 1);
	i = ft_strlcat(top, title, size + 1);
	c_count = 4 + ft_strlen(title);
	top[i++] = ' ';
	ft_strlcat(top, cc, size + 1);
	while (c_count < width)
	{
		i = ft_strlcat(top, "─", i + 4);
		c_count++;
	}
	i = ft_strlcat(top, "╮\n", i + 6);
	return (top);
}

static char	*ft_add_spaces(char *ret, char *split, int longest)
{
	int		j;

	j = (int)ft_strlen(split);
	while (j < longest)
	{
		ft_strlcat(ret, " ", 2000);
		j++;
	}
	return (ret);
}

static char	*ft_get_content(char *cc, int longest, char **split)
{
	int		i;
	char	*ret;

	i = 0;
	ret = ft_calloc(20000, sizeof(char));
	if (!ret)
		return (NULL);
	while (split[i])
	{
		ft_strlcat(ret, cc, 2000);
		ft_strlcat(ret, "│ ", 2000);
		ft_strlcat(ret, split[i], 2000);
		ret = ft_add_spaces(ret, split[i], longest);
		ft_strlcat(ret, " │\n", 20000);
		i++;
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
	CC = Content color and Border color
*/
void	outline(char *title, char *content, char *tc, char *cc)
{
	int				longest;
	int				i;
	char			**split;
	char			*ret;

	split = ft_split(content, '\n');
	i = 0;
	longest = 0;
	while (split[i])
	{
		if ((int)ft_strlen(split[i]) > longest)
			longest = ft_strlen(split[i]);
		i++;
	}
	ret = ft_get_top(title, longest + 4, tc, cc);
	printf("%s", ret);
	free(ret);
	ret = ft_get_content(cc, longest, split);
	printf("%s", ret);
	free(ret);
	ret = ft_get_bottom(longest + 4);
	printf("%s", ret);
	free(ret);
	ft_free_env(split);
}
