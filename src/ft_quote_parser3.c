/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_parser3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:40:01 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/25 18:05:18 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_get_dquote(t_minishell *shell, char *str)
{
	int		i;
	int		len;
	char	*var_val;
	char	*new;
	char	*tmp;

	i = 0;
	new = ft_calloc(1, sizeof(char));
	if (!new)
		return (ft_error(shell, "Could not allocate memory\n", 1), NULL);
	len = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			len = ft_get_var_len(str + i);
			var_val = ft_get_var_value(shell, ft_substr(str + i, 1, len));
			tmp = ft_substr(str + i, 0, len);
			if (!var_val)
				i += ft_strlen(tmp);
			else
			{
				new = ft_strjoin_free(new, var_val, 1, 0);
				i += len;
			}
			free(var_val);
			free(tmp);
		}
		else
		{
			new = ft_strjoin_free(new, ft_substr(str + i, 0, 1), 1, 1);
			i++;
		}
	}
	return (new);
}

char	*ft_parse_dqoute(t_minishell *shell, char *str, char *qstart, char *qend)
{
	char	*new;

	new = ft_get_dquote(shell, ft_substr(str, qstart - str + 1, qend - qstart - 1));
	if (!new)
		return (ft_error(shell, "Could not allocate memory for new string\n", 1), NULL);
	shell->parms = (char **) malloc(2 * sizeof(char *));
	if (!shell->parms)
		return (ft_error(shell, "Could not allocate memory for shell->parms\n", 1), NULL);
	shell->quotes = true;
	return (new);
}
