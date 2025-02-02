/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:31:56 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/30 11:27:58 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

//	FT_ENVP.C
int		ft_add_exists_var(t_minishell *shell, char *var);
int		ft_add_var(t_minishell *shell, char *var, bool system);
int		ft_delete_var(t_minishell *shell, char *var);
char	*ft_get_var_value(t_minishell *shell, char *var);
char	*ft_get_var_name(char *line);

//	FT_ENVP2.C
void	ft_free_env(char **env);
bool	ft_check_validity(t_minishell *shell, char *var);
int		ft_tablen(char **tab, int is_echo);
char	**ft_init_env(char **envp);

// EXPORT/FT_CUSTOM_QPARSER.C
char	**ft_custom_qparser(t_minishell *shell);

#endif
