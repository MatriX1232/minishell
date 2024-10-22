/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parms.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 13:39:27 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/23 01:51:03 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARMS_H
# define PARMS_H

# include "../../include/minishell.h"
# include "../../include/structures.h"
# include "../../include/libraries.h"

void	ft_rm_parm(t_minishell *shell, int idx);
void	ft_add_parm(t_minishell *shell, int idx, char *value);

void	ft_rm_parm(t_minishell *shell, int idx);
void	ft_add_parm(t_minishell *shell, int idx, char *value);

#endif
