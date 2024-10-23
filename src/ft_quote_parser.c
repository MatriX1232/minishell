/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:41:31 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/23 19:10:05 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libraries.h"
#include "../include/structures.h"
#include "quotes/quotes.h"

void	ft_squote(char *str, char *ret, int *i)
{
	int		j;
	char	*new;

	j = *i + 1;
	while (str[j] && str[j] != 39)
		j++;
	if (!str[j])
		j--;
	new = ft_substr(str, *i + 1, j - *i - 1);
	ft_strlcat(ret, new, 10000);
	free(new);
	*i = j + 1;
}

void	ft_dquote(t_minishell *shell, char *str, char *ret, int *i)
{
	int		j;
	char	*tmp;

	j = *i + 1;
	while (str[j] && str[j] != '\"')
		j++;
	if (!str[j] || j == *i + 1)
	{
		*i = j;
		return ;
	}
	else
		tmp = ft_pdquote(shell, str + *i);
	ft_strlcat(ret, tmp, 10000);
	free(tmp);
	(*i)++;
	while (str[*i] && str[*i] != '\"')
		(*i)++;
	if (!str[*i])
		(*i)--;
	(*i)++;
}

void	ft_vars(t_minishell *shell, char *str, char *ret, int *i)
{
	char	*tmp;
	char	*var;

	if (str[*i + 1] == '?')
		tmp = ft_strdup("?");
	else
		tmp = ft_get_var_name(str + *i);
	if (str[*i] == '$' && (ft_intab(str[*i + 1], " \t \0") || !str[*i + 1]))
		var = ft_strdup("$");
	else
		var = ft_get_var_value(shell, tmp);
	if (!var)
		var = ft_strdup("");
	ft_strlcat(ret, var, 10000);
	free(var);
	*i += ft_strlen(tmp) + 1;
	free(tmp);
}

void	ft_qparser_shell(t_minishell *shell, char *str)
{
	int		i;
	char	*ret;

	ret = ft_malloc_ret(shell, &i);
	while (str[i])
	{
		if (str[i] == '$')
			ft_vars(shell, str, ret, &i);
		else if (str[i] == '\"')
			ft_dquote(shell, str, ret, &i);
		else if (str[i] == '\'')
			ft_squote(str, ret, &i);
		else if (str[i] == ' ' || str[i] == '\t')
		{
			ft_strcat_char(ret, SPLIT_SEP);
			while (str[i] && (str[i] == ' ' || str[i] == '\t'))
				i++;
		}
		else if (str[i] == '>' || str[i] == '<' || str[i] == '|')
			ft_redirection(str, ret, &i);
		else
			ft_normal(str, ret, &i);
	}
	ft_move_split(shell, ret);
	free(ret);
}
