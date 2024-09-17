/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_quote_parser.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/09 16:41:31 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/17 16:42:47 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
#include "../include/libraries.h"
#include "../include/structures.h"

static int	ft_get_var_len(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] > 32)
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

//	TODO:	Check if var is freed
char	*ft_get_dquote(t_minishell *shell, char *str)
{
	int		i;
	int		len;
	char	*var_val;
	char	*new;

	i = 0;
	new = ft_calloc(1, sizeof(char));
	if (!new)
		return (ft_error(shell, "Could not allocate memory for new string\n", 1), NULL);
	len = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			len = ft_get_var_len(str + i);
			var_val = ft_get_var_value(shell, ft_substr(str + i, 1, len));
			if (!var_val)
				i += ft_strlen(ft_substr(str + i, 0, len));
			else
			{
				new = ft_strjoin_free(new, var_val);
				i += len;
			}
		}
		else
		{
			new = ft_strjoin_free(new, ft_substr(str + i, 0, 1));
			i++;
		}
	}
	return (new);
}

static void	ft_parse_sqoute(t_minishell *shell, char *str, char *qstart, char *qend)
{
	char	*new;

	new = ft_substr(str, qstart - str + 1, qend - qstart - 1);
	if (!new)
		return ft_error(shell, "Could not allocate memory for new string\n", 1);
	shell->parms = (char **) malloc(2 * sizeof(char *));
	if (!shell->parms)
		return ft_error(shell, "Could not allocate memory for shell->parms\n", 1);
	shell->parms[1] = new;
	shell->parms[0] = ft_substr(str, 0, ft_strchr(str, ' ') - str);
	shell->quotes = true;
}

// static void	ft_parse_dqoute(t_minishell *shell, char *str, char *qstart, char *qend)
char	*ft_parse_dqoute(t_minishell *shell, char *str, char *qstart, char *qend)
{
	char	*new;

	new = ft_get_dquote(shell, ft_substr(str, qstart - str + 1, qend - qstart - 1));
	if (!new)
		return (ft_error(shell, "Could not allocate memory for new string\n", 1), NULL);
	shell->parms = (char **) malloc(2 * sizeof(char *));
	if (!shell->parms)
		return (ft_error(shell, "Could not allocate memory for shell->parms\n", 1), NULL);
	// shell->parms[1] = new;
	// shell->parms[0] = ft_substr(str, 0, ft_strchr(str, ' ') - str);
	shell->quotes = true;
	return (new);
}

static void	ft_parse_normal(t_minishell *shell)
{
	int		i;
	char	*val;
	char	**parms;

	i = 0;
	parms = shell->parms;
	while (parms[i])
	{
		if (parms[i][0] == '$')
		{
			val = ft_get_var_value(shell, parms[i] + 1);
			if (val)
			{
				free(parms[i]);
				parms[i] = val;
			}
		}
		i++;
	}
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

void	ft_qparser_shell(t_minishell *shell, char *str)
{
	int		i;
	int		j;;
	char	*new;
	char	*ret;

	(void)ft_parse_normal;
	(void)ft_parse_sqoute;
	ret = (char *) ft_calloc(1000, sizeof(char));
	if (!ret)
		return ft_error(shell, "Could not calloc\n", 1);
	i = 0;
	while (str[i])
	{
		if (str[i] == 34)
		{
			j = i + 1;
			while (str[j] && str[j] != 34)
				j++;
			new = ft_parse_dqoute(shell, str, str + i, str + j);
			// ret = ft_malloc_more(ret, ft_strlen(new));
			ft_strlcat(ret, new, ft_strlen(new) + 1);
			i += ft_strlen(new) + 1;
		}
		else if (str[i] == 39)
		{
			j = i + 1;
			while (str[j] && str[j] != 39)
				j++;
			new = ft_substr(str, i + 1, j - i - 1);
			ft_strlcat(ret, new, ft_strlen(new) + 1);
			i += ft_strlen(new) + 1;
		}
		else
		{
			ft_strlcat(ret, str + i, 1);
			i++;
		}
		printf("RET = %s\n", ret);
	}
	shell->parms[0] = ft_substr(str, 0, ft_strchr(str, ' ') - str);
	shell->parms[1] = ret;
	shell->quotes = true;
}

// void	ft_qparser_shell(t_minishell *shell, char *str)
// {
// 	char	*qstart;
// 	char	*qend;

// 	qstart = ft_strchr(str, '"');
// 	qend = ft_strrchr(str, '"');
// 	if (qstart && qend && qstart != qend)
// 		return ft_parse_dqoute(shell, str, qstart, qend);
// 	qstart = ft_strchr(str, 39);
// 	qend = ft_strrchr(str, 39);
// 	if (qstart && qend && qstart != qend)
// 		return ft_parse_sqoute(shell, str, qstart, qend);
// 	else
// 	{
// 		shell->parms = ft_split(str, ' ');
// 		shell->quotes = false;
// 		ft_parse_normal(shell);
// 	}
// }
