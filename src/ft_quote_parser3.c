/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_parser3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:40:01 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/21 13:32:49 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_parser3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:40:01 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/20 15:56:42 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_parser3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 15:40:01 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/20 15:56:42 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*ft_var_expand(t_minishell *shell, char *str, int *i)
{
	int		len;
	char	*var_val;
	char	*tmp;

	len = ft_get_var_len(str + *i);
	tmp = ft_substr(str + *i, 1, len); // extract variable name without $
	var_val = ft_get_var_value(shell, tmp);
	free(tmp);
	if (!var_val)
		*i += len + 1; // increment by the length of variable + '$'
	return (var_val);
}

char	*ft_get_dquote(t_minishell *shell, char *str)
{
	int		i;
	char	*var_val;
	char	*new;
	char	*tmp;

	i = 0;
	new = ft_calloc(1, sizeof(char));
	if (!new)
		return (ft_error(shell, "Memory allocation error\n", 1), NULL);
	while (str[i])
	{
		if (str[i] == '$')
		{
			var_val = ft_var_expand(shell, str, &i);
			if (var_val)
			{
				tmp = new;
				new = ft_strjoin_free(new, var_val);
				free(tmp); // Free the old new before updating it
			}
		}
		else
		{
			tmp = new;
			new = ft_strjoin_free(new, ft_substr(str, i, 1)); // copy single char
			free(tmp); // Free the old new before updating it
			i++; // Increment for the next character
		}
	}
	return (new);
}

char	*ft_parse_dqoute(t_minishell *shell, char *str, char *qstart, char *qend)
{
	char	*new;

	new = ft_get_dquote(shell, ft_substr(str, qstart - str + 1, qend - qstart - 1));
	if (!new)
		return (ft_error(shell, "Memory allocation error\n", 1), NULL);
	shell->parms = (char **)malloc(2 * sizeof(char *));
	if (!shell->parms)
		return (ft_error(shell, "Memory allocation error\n", 1), NULL);
	shell->quotes = true;
	return (new);
}


// static char	*ft_vars(t_minishell *shell, char *str, int *i, int *len)
// {
// 	char	*var_val;

// 	len = ft_get_var_len(str + i);
// 	var_val = ft_get_var_value(shell, ft_substr(str + i, 1, len));
// 	if (!var_val)
// 		i += ft_strlen(ft_substr(str + i, 0, len));
// 	else
// 	{
// 		new = ft_strjoin_free(new, var_val);
// 		i += len;
// 	}
// }

//	TODO:	Check if var is freed
// char	*ft_get_dquote(t_minishell *shell, char *str)
// {
// 	int		i;
// 	int		len;
// 	char	*var_val;
// 	char	*new;

// 	i = 0;
// 	new = ft_calloc(1, sizeof(char));
// 	if (!new)
// 		return (ft_error(shell, "Could not allocate memory for new string\n", 1), NULL);
// 	len = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '$')
// 		{
// 			len = ft_get_var_len(str + i);
// 			var_val = ft_get_var_value(shell, ft_substr(str + i, 1, len));
// 			if (!var_val)
// 				i += ft_strlen(ft_substr(str + i, 0, len));
// 			else
// 			{
// 				new = ft_strjoin_free(new, var_val);
// 				i += len;
// 			}
// 		}
// 		else
// 		{
// 			new = ft_strjoin_free(new, ft_substr(str + i, 0, 1));
// 			i++;
// 		}
// 	}
// 	return (new);
// }

// char	*ft_parse_dqoute(t_minishell *shell, char *str, char *qstart, char *qend)
// {
// 	char	*new;

// 	new = ft_get_dquote(shell, ft_substr(str, qstart - str + 1, qend - qstart - 1));
// 	if (!new)
// 		return (ft_error(shell, "Could not allocate memory for new string\n", 1), NULL);
// 	shell->parms = (char **) malloc(2 * sizeof(char *));
// 	if (!shell->parms)
// 		return (ft_error(shell, "Could not allocate memory for shell->parms\n", 1), NULL);
// 	shell->quotes = true;
// 	return (new);
// }
