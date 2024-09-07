/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:01:29 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/07 22:34:29 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libraries.h"
#include "../include/minishell.h"

static char	*ft_transfer(char *base, char *addition)
{
	char	*new;

	new = ft_strjoin(base, addition);
	if (!new)
		return (NULL);
	free(base);
	return (new);
}

static char	*ft_readline(int fd, char *left, char *buffer, int BF)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BF);
		if (bytes_read == -1)
			return (free(left), NULL);
		else if (bytes_read == 0)
			break ;
		buffer[bytes_read] = '\0';
		if (!left)
			left = ft_strdup("");
		left = ft_transfer(left, buffer);
		if (!left)
			return (free(left), NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (left);
}

static char	*ft_return_left(char *line)
{
	size_t	i;
	char	*left;

	i = 0;
	while (line[i] != '\n' && line[i] != '\0')
		i++;
	if (line[i] == '\0')
		return (NULL);
	left = ft_substr(line, i + 1, ft_strlen(line) - i);
	if (left[0] == '\0')
	{
		free(left);
		left = NULL;
	}
	line[i + 1] = '\0';
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*buffer_all = NULL;
	char		*buffer;
	char		*line;
	int			BUFFER_SIZE;

	BUFFER_SIZE = 40;
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = ft_readline(fd, buffer_all, buffer, BUFFER_SIZE);
	free(buffer);
	if (!line)
	{
		free(line);
		return (NULL);
	}
	buffer_all = ft_return_left(line);
	return (line);
}
