/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msolinsk <msolinsk@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:33:10 by msolinsk          #+#    #+#             */
/*   Updated: 2024/10/16 13:30:57 by msolinsk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

# include <stdbool.h>

# define END "\x1b[0m"
# define BOLD "\x1b[1m"
# define UNDER "\x1b[4m"
# define REV "\x1b[7m"
# define GREY "\x1b[30m"
# define RED "\x1b[31m"
# define GREEN "\x1b[32m"
# define YELLOW "\x1b[33m"
# define BLUE "\x1b[34m"
# define PURPLE "\x1b[35m"
# define CYAN "\x1b[36m"
# define WHITE "\x1b[37m"

typedef struct s_pipe
{
	int		count;
	int		*pid;
	int		redirect;
	bool	here_doc;
}	t_pipe;

typedef struct s_minishell
{
	t_pipe	pipe;
	char	*cwd;
	char	*print_prefix_success;
	char	*print_prefix_failure;
	char	**parms;
	bool	quotes;
	char	**argv;
	char	**env;
	char	*raw_parsed;
}	t_minishell;

typedef struct s_Command
{
	char	**args;
	char	*input_file;
	char	*output_file;
	char	*heredoc_delim;
	int		append;
}	Command;

#endif
