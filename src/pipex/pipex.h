/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:10:06 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/23 16:23:44 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include "../../include/structures.h"
#include "../../include/minishell.h"
#include "../../include/libraries.h"

// FT_PIPE.C
int		execute_commands(t_minishell *shell, t_Command *commands, int cmd_count);
int		parse_commands(t_minishell *shell, char **parms, t_Command **commands);


// FT_PIPE2.C
int		ptr_to_idx(char *str, char *ptr);
int		is_builtin(char *command);
int		ft_detect_pipe(t_minishell *shell);
int		ft_isbuiltin(char *cmd);
void	execute_builtin(t_minishell *shell, char **args);

#endif
