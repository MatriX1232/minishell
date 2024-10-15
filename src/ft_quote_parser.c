/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:41:31 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/15 13:31:31 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libraries.h"
#include "../include/structures.h"
#include "quotes/quotes.h"

static void	ft_squote(char *str, char *ret, int *i)
{
	int		j;
	char	*new;

	j = *i + 1;
	while (str[j] && str[j] != 39)
		j++;
	new = ft_substr(str, *i + 1, j - *i - 1);
	ft_strlcat(ret, new, 1000);
	free(new);
	*i = j + 1;
}

static void	ft_dquote(t_minishell *shell, char *str, char *ret, int *i)
{
	char	*tmp;

	tmp = ft_pdquote(shell, str + *i);
	ft_strlcat(ret, tmp, ft_strlen(ret) + ft_strlen(tmp) + 1);
	free(tmp);
	(*i)++;
	while (str[*i] && str[*i] != '\"')
		(*i)++;
	(*i)++;
}

static void	ft_vars(t_minishell *shell, char *str, char *ret, int *i)
{
	char	*tmp;
	char	*var;

	tmp = ft_get_var_name(str + *i);
	var = ft_get_var_value(shell, tmp);
	if (!var)
		var = ft_strdup("");
	ft_strlcat(ret, var, 10000);
	free(var);
	*i += ft_strlen(tmp) + 1;
	free(tmp);
}

static void	ft_normal(char *str, char *ret, int *i)
{
	int	j;

	j = ft_strlen(ret);
	ret[j] = str[*i];
	ret[j + 1] = '\0';
	(*i)++;
}

//	TODO:	Change to 10 000 in PROD
void	ft_qparser_shell(t_minishell *shell, char *str)
{
	int		i;
	char	*ret;

	ret = (char *) ft_calloc(10000, sizeof(char));
	if (!ret)
		return (ft_error(shell, "Could not calloc\n", 1));
	i = 0;
	while (str[i] && str[i] != ' ')
		i++;
	while (str[i] && (str[i] == ' ' || str[i] == '\t'))
		i++;
	while (str[i])
	{
		if (str[i] == '$')
			ft_vars(shell, str, ret, &i);
		else if (str[i] == '\"')
			ft_dquote(shell, str, ret, &i);
		else if (str[i] == '\'')
			ft_squote(str, ret, &i);
		else
			ft_normal(str, ret, &i);
	}
	ft_move_split(shell, str, ret);
	free(ret);
	int j = 0;
	while (shell->parms[j])
	{
		printf("shell->parms[%d]: %s\n", j, shell->parms[j]);
		j++;
	}
	if (shell->parms[j] == NULL)
		printf("shell->parms[%d]: %s\n", j, shell->parms[j]);
}
