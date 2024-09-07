/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:13:09 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/07 21:16:09 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libraries.h"
# include "structures.h"
# include "../src/builtins/builtins.h"

//	FT_FREE.C
void	ft_free_shell(t_minishell *shell);

//	FT_ERROR.C
void	ft_error(t_minishell *shell, char *message);

#endif
