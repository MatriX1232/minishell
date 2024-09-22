/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_parser2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:18:09 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/22 17:51:39 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	ft_get_var_len(char *str)
{
	int		i;

	i = 0;
	while (str[i] && (ft_isalnum(str[i]) || str[i] == '_'))
		i++;
	return (i - 1);
}

char	*ft_strjoin_free(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	int		i;
	char	*str;

	len1 = 0;
	len2 = 0;
	while (s1[len1])
		len1++;
	while (s2[len2])
		len2++;
	str = (char *)ft_calloc((len1 + len2 + 1), sizeof(char));
	if (str == NULL)
		return (NULL);
	i = -1;
	while (i++ < len1)
		str[i] = (char)s1[i];
	i = -1;
	while (i++ < len2)
		str[len1 + i] = (char)s2[i];
	free((char *)s1);
	return (str);
}

char	*ft_malloc_more(char *old, int n)
{
	char	*new;

	new = (char *) malloc((ft_strlen(old) + n + 1) * sizeof(char));
	if (!new)
		return (ft_error(NULL, "Could not allocate more alloc\n", 0), NULL);
	ft_strlcpy(new, old, ft_strlen(old) + 1);
	new[ft_strlen(new)] = '\0';
	free(old);
	return (new);
}

void	ft_move_split(t_minishell *shell, char *str, char *ret)
{
	int		i;
	char	**split;

	split = ft_split(ret, ' ');
	if (!split)
		return (ft_error(shell, "Could not split\n", 1));
	shell->parms = (char **) malloc((ft_tab_len(split) + 2) * sizeof(char *));
	if (!shell->parms)
		return (ft_error(shell, "Could not allocate memory\n", 1));
	shell->parms[0] = ft_substr(str, 0, ft_strchr(str, ' ') - str);
	i = 1;
	while (split[i - 1])
	{
		shell->parms[i] = split[i - 1];
		i++;
	}
	shell->parms[i] = NULL;
}
