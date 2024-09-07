/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 22:01:29 by msolinsk          #+#    #+#             */
/*   Updated: 2024/06/14 18:42:41 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_transfer(char *base, char *addition)
{
	char	*new;

	new = ft_strjoin(base, addition);
	if (!new)
		return (NULL);
	free(base);
	return (new);
}

static char	*ft_strdup(const char *s)
{
	size_t	i;
	size_t	len;
	char	*ptr;

	i = 0;
	len = ft_strlen(s);
	ptr = malloc(len + 1);
	if (ptr == NULL)
	{
		return (NULL);
	}
	while (s[i])
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

static char	*ft_readline(int fd, char *left, char *buffer)
{
	ssize_t	bytes_read;

	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
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

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *) malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	line = ft_readline(fd, buffer_all, buffer);
	free(buffer);
	if (!line)
	{
		free(line);
		return (NULL);
	}
	buffer_all = ft_return_left(line);
	return (line);
}

// char	*ft_move_offset(char *buffer)
// {
// 	int		index;
// 	int		i;
// 	char	*new;

// 	if (*buffer == '\0')
// 	{
// 		free(buffer);
// 		return (NULL);
// 	}
// 	index = 0;
// 	while (buffer[index] && buffer[index] != '\n')
// 		index++;
// 	new = ft_calloc(ft_strlen(buffer) - index + 1, sizeof(char));
// 	if (!new)
// 		return (NULL);
// 	index++;
// 	i = 0;
// 	while (buffer[index + i])
// 	{
// 		new[i] = buffer[index + i];
// 		i++;
// 	}
// 	new[i] = '\0';
// 	free(buffer);
// 	return (new);
// }

// static char	*ft_extract_line(char *buffer)
// {
// 	int		index;
// 	int		i;
// 	char	*line;

// 	index = 0;
// 	while (buffer[index] && buffer[index] != '\n')
// 		index++;
// 	line = ft_calloc(index + 2, sizeof(char));
// 	if (!line)
// 		return (NULL);
// 	i = 0;
// 	while (i < index && buffer[i])
// 	{
// 		line[i] = buffer[i];
// 		i++;
// 	}
// 	if (buffer[index] == '\n')
// 		line[i++] = '\n';
// 	line[i] = '\0';
// 	if (*line == '\0')
// 	{
// 		free(line);
// 		return (NULL);
// 	}
// 	return (line);
// }

// static char	*ft_readline(int fd, char *buffer, char *buffer_all)
// {
// 	// int		bytes_read;
//
// 	if (!buffer_all)
// 		buffer_all = ft_calloc(1, 1);
// 	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
// 	bytes_read = 1;
// 	while (bytes_read > 0)
// 	{
// 		bytes_read = read(fd, buffer, BUFFER_SIZE);
// 		if (bytes_read == -1)
// 		{
// 			free(buffer);
// 			return (NULL);
// 		}
// 		buffer[bytes_read] = '\0';
// 		buffer_all = ft_transfer(buffer_all, buffer);
// 		if (ft_strchr(buffer, '\n'))
// 			break ;
// 	}
// 	free(buffer);
// 	return (buffer_all);
// }
