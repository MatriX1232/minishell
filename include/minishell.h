/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:13:09 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/23 17:20:27 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libraries.h"
# include "structures.h"

//	FT_OUTLINE.C
void	outline(char *title, char *content, char *tc, char *cc);

//	FT_SIGNALS.C
void	sig_ctrlc(int sig);
void	sig_term(int sig);
void	sig_segv(int sig);
void	sig_abort(int sig);

//	FT_ANIM.C
void	ft_animate_ship(void);

//	FT_PARSE.C
int		ft_parse(t_minishell *shell, char *line);

// FT_PARSE2.C
int		get_path(char **env);
char	*get_exe(char *cmd, char *path);
char	*get_cmd(char *line);
int		ft_check(char *exe);

//	FT_QUOTE_PARSER.C
char	*ft_qparser(char *str);
void	ft_qparser_shell(t_minishell *shell, char *str);
void	ft_squote(char *str, char *ret, int *i);
void	ft_dquote(t_minishell *shell, char *str, char *ret, int *i);
void	ft_vars(t_minishell *shell, char *str, char *ret, int *i);

//	FT_QUOTE_PARSER2.C
int		ft_get_tab_len(char **tab);
int		ft_get_var_len(char *str);
char	*ft_strjoin_free(char const *s1, char const *s2, bool f1, bool f2);
char	*ft_malloc_more(char *old, int n);
void	ft_move_split(t_minishell *shell, char *ret);

//	FT_QUOTE_PARSER3.C
void	ft_strcat_char(char *dest, char c);
char	*ft_strncat(char *dest, const char *src, int n);
void	ft_redirection(char *str, char *ret, int *i);
void	ft_normal(char *str, char *ret, int *i);
void	checks_for_qparse(t_minishell *shell, char *str, int *i, char *ret);
bool	ft_is_closed(char *str, char q);

//	FT_FREE.C
void	ft_free_shell(t_minishell *shell);
void	ft_free_parms(t_minishell *shell);

//	FT_PRINT.C
void	ft_error(t_minishell *shell, char *message, int shell_failure);
void	ft_success(t_minishell *shell);
int		ft_check_line(char *line);

//	FT_REALLOC.C
void	*ft_realloc(void *ptr, size_t size, size_t old_size);

//	GNL.C
char	*get_next_line(int fd);

//	FT_EXEC.C
int		ft_exec(t_minishell *shell, char *line);

//	FT_PIPE.C
int		parse_commands(t_minishell *shell, char **parms, t_Command **commands);
int		execute_commands(t_minishell *shell, t_Command *commands, int cmd_count);
int		ft_detect_pipe(t_minishell *shell);

// FT_EXIT.C
int		ft_exit(t_minishell *shell, char *line);

#endif
