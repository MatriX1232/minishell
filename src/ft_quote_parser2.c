/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_parser2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:18:09 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/17 13:22:41 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "quotes/quotes.h"

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

char	*ft_strjoin_free(char const *s1, char const *s2, bool f1, bool f2)
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
	if (f1)
		free((char *)s1);
	if (f2)
		free((char *)s2);
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

void	ft_move_split(t_minishell *shell, char *ret)
{
	int		i;
	char	**split;

	split = ft_split(ret, SPLIT_SEP);
	if (!split)
		return (ft_error(shell, "Could not split\n", 1));
	shell->parms = (char **)malloc((ft_tablen(split, 0) + 1) * sizeof(char *));
	if (!shell->parms)
		return (ft_error(shell, "Could not allocate memory\n", 1));
	i = 0;
	while (split[i])
	{
		shell->parms[i] = ft_strdup(split[i]);
		i++;
	}
	shell->parms[i] = NULL;
	ft_free_env(split);
}