/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 18:02:50 by msolinsk          #+#    #+#             */
/*   Updated: 2024/06/15 13:54:56 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	int		j;
	char	*new;

	if (!s1 || !s2)
		return (NULL);
	new = (char *) malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		new[i + j] = s2[j];
		j++;
	}
	*(new + i + j) = '\0';
	return (new);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (*s == '\0' && c == '\0')
	{
		return ((char *)s);
	}
	while (*(s + i))
	{
		if (*(s + i) == c)
		{
			return ((char *)(s + i));
		}
		i++;
	}
	if (*(s + i) == c)
	{
		return ((char *)(s + i));
	}
	return (NULL);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (!s)
		return (NULL);
	if (start > ft_strlen(s))
		return (malloc(1));
	if (len > ft_strlen(s + start))
		len = ft_strlen(s + start);
	str = malloc((len + 1) * sizeof(char));
	if (!str)
		return (NULL);
	i = 0;
	while (i < len)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = 0;
	return (str);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	void			*array;
	unsigned char	*p;
	int				n;

	if ((int)(nmemb * size) > 2147483647 || (int)(nmemb * size) < -2147483648)
		return (NULL);
	array = (void *) malloc(size * nmemb);
	if (!array)
		return (NULL);
	p = (unsigned char *) array;
	n = nmemb * size;
	while (n > 0)
	{
		*p = 0;
		p++;
		n--;
	}
	return (array);
}
