/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idomagal <idomagal@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:13:09 by msolinsk          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/11 14:04:47 by idomagal         ###   ########.fr       */
=======
/*   Updated: 2024/09/11 12:58:24 by msolinsk         ###   ########.fr       */
>>>>>>> c7f9780 (Fixed export and unset)
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
int		check_pipe(char *line);
int		get_path(char **env);
char	*get_exe(char *cmd, char *path);
char	*get_cmd(char *line);

//	FT_QUOTE_PARSER.C
char	*ft_qparser(char *str);
void	ft_qparser_shell(t_minishell *shell, char *str);

//	FT_FREE.C
void	ft_free_shell(t_minishell *shell);
<<<<<<< HEAD
void	ft_free_parms(char **parms);
=======
void	 ft_free_parms(t_minishell *shell);
>>>>>>> c7f9780 (Fixed export and unset)

//	FT_PRINT.C
void	ft_error(t_minishell *shell, char *message, int shell_failure);
void	ft_success(t_minishell *shell);

//	GNL.C
char	*get_next_line(int fd);

//	FT_EXEC.C
int		ft_exec(t_minishell *shell, char *line);

//	FT_PIPE.C
int		pipex(int args, char **argv, char **env);

#endif
