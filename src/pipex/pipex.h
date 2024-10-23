/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 15:10:06 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/23 17:54:17 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../../include/libraries.h"
# include "../../include/structures.h"
# include "../../include/minishell.h"

// FT_PIPE.C
int		execute_commands(t_minishell *shell, t_Command *commands, int cmd_c);
int		parse_commands(t_minishell *shell, char **parms, t_Command **commands);

// FT_PIPE2.C
int		ptr_to_idx(char *str, char *ptr);
int		is_builtin(char *command);
int		ft_detect_pipe(t_minishell *shell);
int		ft_isbuiltin(char *cmd);
void	execute_builtin(t_minishell *shell, char **args);

// FT_PIPES_UTILS.C
void	ft_if_first_red(t_minishell *sh, t_Command **cd, t_vars *vs, char **p);
void	ft_cc_more_cs(t_minishell *shell, t_Command **cmds, t_vars *vars);
void	ft_if_pipe(t_Command **cmds, int cmdc, int *ax, int *as);
void	ft_last_else(t_minishell *shell, t_Command **cmds, t_vars *vars);
int		ft_init_cmds(t_minishell *shell, t_Command **cmds, t_vars *vars);

// FT_PIPES_UTILS2.C
void	ft_all_ifs(t_minishell *sh, t_Command **cmds, t_vars *vars, char **ps);

//	FT_PIPES_EXEC_UTILS.C
void	ft_no_input_file(t_evars *evars, t_minishell *sh, t_Command *cd, int i);
void	ft_no_output_files(t_evars *ev, t_minishell *sh, t_Command *cd, int i);
void	ft_no_heredoc_delim(t_evars *evars, t_Command *commands, int i);
void	ft_create_pipes(t_evars *evars, t_minishell *shell);
void	ft_no_heredoc_main(t_evars *evars, t_minishell *shell, t_Command *cmds, int i);

#endif
