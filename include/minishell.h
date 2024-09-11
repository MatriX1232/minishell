/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idomagal <idomagal@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:13:09 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/11 13:29:20 by idomagal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libraries.h"
# include "structures.h"
# include "../src/builtins/builtins.h"

//	FT_SIGNALS.C
void	sig_ctrlc(int sig);
void	sig_ctrl_bslash(int sig);

//	FT_PARSE.C
int		ft_parse(t_minishell *shell, char *line);
int		check_pipe(t_minishell *shell, char *line);
int		get_path(char **env, int help, int argc, char **argv);
char	*get_exe(char *cmd, char *path);

//	FT_QUOTE_PARSER.C
char	*ft_qparser(char *str);
void	ft_qparser_shell(t_minishell *shell, char *str);

//	FT_FREE.C
void	ft_free_shell(t_minishell *shell);
void	 ft_free_parms(char **parms);

//	FT_ERROR.C
void	ft_error(t_minishell *shell, char *message, int shell_failure);
void	ft_success(t_minishell *shell);

//	GNL.C
char	*get_next_line(int fd);

// FT_PIPE.C
int		pipex(int args, char **argv, char **env);

#endif
