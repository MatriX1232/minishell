/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:31:56 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/11 15:02:28 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef BUILTINS_H
# define BUILTINS_H

# include "../../include/structures.h"
# include "../../include/libraries.h"
# include "../../include/minishell.h"

int		ft_pwd(t_minishell *shell);
int		ft_echo(t_minishell *shell);
int		ft_cd(t_minishell *shell);
int		ft_env(t_minishell *shell);
int		ft_unset(t_minishell *shell);
int		ft_export(t_minishell *shell);

bool	ft_exists_var(t_minishell *shell, char *var_name);
int		ft_add_var(t_minishell *shell, char *var);
int		ft_delete_var(t_minishell *shell, char *var);

#endif
