/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 11:37:52 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/16 21:45:49 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUOTES_H
# define QUOTES_H

# include "../../include/libraries.h"
# include "../include/minishell.h"

char	*ft_pdquote(t_minishell *shell, char *line);
bool	ft_intab(char c, char *tab);

#endif
