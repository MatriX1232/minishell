/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:13:09 by msolinsk          #+#    #+#             */
/*   Updated: 2024/09/25 18:04:00 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libraries.h"
# include "structures.h"
# include "../src/builtins/builtins.h"

//	FT_SIGNALS.C
void	sig_ctrlc(int sig);
void	sig_term(int sig);
void	sig_segv(int sig);
void	sig_abort(int sig);

//	FT_ANIM.C
void	ft_animate_ship(void);

//	FT_PARSE.C
int		ft_parse(t_minishell *shell, char *line);
int		check_pipe(char *line);
int		get_path(char **env);
char	*get_exe(char *cmd, char *path);
char	*get_cmd(char *line);

//	FT_QUOTE_PARSER.C
char	*ft_qparser(char *str);
void	ft_qparser_shell(t_minishell *shell, char *str);

//	FT_QUOTE_PARSER2.C
int		ft_get_tab_len(char **tab);
int		ft_get_var_len(char *str);
char	*ft_strjoin_free(char const *s1, char const *s2, bool f1, bool f2);
char	*ft_malloc_more(char *old, int n);
void	ft_move_split(t_minishell *shell, char *str, char *ret);

//	FT_QUOTE_PARSER3.c
char	*ft_get_dquote(t_minishell *shell, char *str);
char	*ft_parse_dqoute(t_minishell *shell, char *str, char *start, char *end);

//	FT_FREE.C
void	ft_free_shell(t_minishell *shell);
void	ft_free_parms(t_minishell *shell);

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
