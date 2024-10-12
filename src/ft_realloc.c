/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/06 21:08:48 by idomagal          #+#    #+#             */
/*   Updated: 2024/10/13 00:09:34 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libraries.h"

void	*ft_realloc(void *ptr, size_t size, size_t old_size)
{
	void	*new;

	if (ptr == NULL)
		return (ft_calloc(size, 1));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new = ft_calloc(size, 1);
	if (new == NULL)
		return (NULL);
	ft_memcpy(new, ptr, old_size);
	free(ptr);
	return (new);
}
