/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:41:31 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/25 16:22:42 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libraries.h"
#include "../include/structures.h"

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
	int		j;
	char	*new;
	char	*trim;

	j = *i + 1;
	while (str[j] && str[j] != 34)
		j++;
	new = ft_get_dquote(shell, str + *i + 1);
	trim = ft_strtrim(new, "\"");
	ft_strlcat(ret, trim, 1000);
	free(new);
	free(trim);
	*i = j + 1;
}

static void	ft_vars(t_minishell *shell, char *str, char *ret, int *i)
{
	char	*tmp;
	char	*var;

	tmp = ft_substr(str + *i, 1, ft_get_var_len(str + *i));
	printf("VAR_NAME: %s\n", tmp);
	var = ft_get_var_value(shell, tmp);
	printf("VAR_VALUE: %s\n", var);
	ft_strlcat(ret, var, 1000);
	printf("ret: %s\n", ret);
	free(var);
	free(tmp);
	*i += ft_strlen(tmp) + 1;
}

static void	ft_normal(char *str, char *ret, int *i)
{
	int	j;

	j = ft_strlen(ret);
	ret[j] = str[*i];
	ret[j + 1] = '\0';
	(*i)++;
}

void	ft_qparser_shell(t_minishell *shell, char *str)
{
	int		i;
	char	*ret;

	ret = (char *) ft_calloc(1000, sizeof(char));
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
		else if (str[i] == 34)
			ft_dquote(shell, str, ret, &i);
		else if (str[i] == 39)
			ft_squote(str, ret, &i);
		else
			ft_normal(str, ret, &i);
		// printf("ret: %s | i: %d | %c\n", ret, i, str[i]);
	}
	ft_move_split(shell, str, ret);
	int	j = 0;
	while (shell->parms[j])
	{
		printf("shell->parms[%d]: %s\n", j, shell->parms[j]);
		j++;
	}
	if (shell->parms[j] == NULL)
		printf("shell->parms[%d]: (null)\n", j);
	free(ret);
}
