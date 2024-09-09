/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:13:09 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/09 17:40:27 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libraries.h"
# include "structures.h"
# include "../src/builtins/builtins.h"

//	FT_PARSE.C
int		ft_parse(t_minishell *shell, char *line);

//	FT_QUOTE_PARSER.C
char	*ft_qparser(char *str);
void	ft_qparser_shell(t_minishell *shell, char *str);

//	FT_FREE.C
void	ft_free_shell(t_minishell *shell);
void	 ft_free_parms(char **parms);

//	FT_ERROR.C
void	ft_error(t_minishell *shell, char *message);
void	ft_success(t_minishell *shell);

//	GNL.C
char	*get_next_line(int fd);

#endif
