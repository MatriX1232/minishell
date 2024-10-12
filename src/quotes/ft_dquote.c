/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_dquote.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:37:42 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/12 23:33:03 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quotes.h"

char	*ft_var_start(t_minishell *shell, char *ret, char *line, int *i)
{
	char	*var_value;
	char	*var_name;
	char	*new_ret;

	var_name = ft_get_var_name(line + *i);
	(*i)++;
	var_value = ft_get_var_value(shell, var_name);
	if (!var_value)
		var_value = ft_strdup("");
	new_ret = ft_strjoin(ret, var_value);
	if (!new_ret)
		return (NULL);
	*i += ft_strlen(var_name);
	free(var_name);
	free(var_value);
	free(ret);
	return (new_ret);
}

//	TODO:	Change to 10 000 in PROD
char	*ft_pdquote(t_minishell *shell, char *line)
{
	int		i;
	char	*ret;
	char	tmp[2];

	i = 1;
	ret = ft_calloc(1000, sizeof(char));
	if (!ret)
		return (NULL);
	while (line[i] && line[i] != '\"')
	{
		if (line[i] == '$')
			ret = ft_var_start(shell, ret, line, &i);
		else
		{
			tmp[0] = line[i];
			tmp[1] = '\0';
			ft_strlcat(ret, tmp, ft_strlen(ret) + 2);
			i++;
		}
	}
	return (ret);
}
