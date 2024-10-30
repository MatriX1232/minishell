/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/08 14:12:54 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/30 11:46:07 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"
#include "../builtins.h"

static void	ft_not_dir(t_minishell *shell)
{
	char	*msg;

	ft_add_var(shell, ft_strdup("?=1"), 1);
	msg = ft_strjoin("<HOME not set> or <", E_MALLOC);
	msg = ft_strjoin_free(msg, ">\n", 1, 0);
	ft_error(shell, msg, 0);
	free(msg);
}

static char	*ft_tilda(t_minishell *shell, char *ret, int *i)
{
	ret = ft_strjoin_free(ret, ft_get_var_value(shell, "HOME"), 1, 1);
	if (!ret)
		return (NULL);
	(*i)++;
	return (ret);
}

static char	*ft_parse_path(t_minishell *shell, char *path)
{
	int		i;
	int		j;
	char	*ret;

	i = 0;
	ret = ft_strdup("");
	while (path[i])
	{
		if (path[i] == '~')
			ret = ft_tilda(shell, ret, &i);
		else
		{
			j = i;
			while (path[j] && path[j] != '~')
				j++;
			ret = ft_strjoin_free(ret, ft_substr(path, i, j), 1, 1);
			if (!ret)
				return (NULL);
			i = j;
		}
	}
	return (ret);
}

int	ft_cd(t_minishell *shell)
{
	char	*dir;
	char	*msg;

	if (ft_tablen(shell->parms, 0) < 2)
	{
		dir = ft_strdup("");
		dir = ft_strjoin_free(dir, ft_get_var_value(shell, "HOME"), 1, 1);
	}
	else
		dir = ft_parse_path(shell, shell->parms[1]);
	if (!dir)
		ft_not_dir(shell);
	if (chdir(dir) == -1)
	{
		ft_add_var(shell, ft_strdup("?=1"), 1);
		msg = ft_strjoin("Could not change directory: ", dir);
		msg = ft_strjoin_free(msg, "\n", 1, 0);
		ft_error(shell, msg, 0);
		free(msg);
		free(dir);
		return (EXIT_FAILURE);
	}
	free(dir);
	ft_add_var(shell, "?=0", 1);
	return (EXIT_SUCCESS);
}
