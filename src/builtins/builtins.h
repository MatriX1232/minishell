/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:31:56 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/08 14:24:54 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../include/structures.h"
# include "../../include/libraries.h"

int	ft_pwd(t_minishell *shell);
int	ft_echo(t_minishell *shell);
int	ft_cd(t_minishell *shell);

#endif
