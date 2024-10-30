/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:37:52 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/30 14:48:36 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_H
# define QUOTES_H

# include "../../include/libraries.h"
# include "../include/minishell.h"

# define INT_TAB_END -1
# define SPLIT_SEP '`'

char	*ft_pdquote(t_minishell *shell, char *line);
bool	ft_intab(char c, char *tab);
int		ft_inttablen(int *tab);
bool	ft_isdq(char *line);

#endif
