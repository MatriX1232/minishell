/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: idomagal <idomagal@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:33:10 by msolinsk          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/11 13:32:12 by idomagal         ###   ########.fr       */
=======
/*   Updated: 2024/09/11 13:09:12 by msolinsk         ###   ########.fr       */
>>>>>>> c7f9780 (Fixed export and unset)
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

# include <stdbool.h>

typedef struct s_minishell
{
	char	*cwd;
	char	*print_prefix_success;
	char	*print_prefix_failure;
	char	**parms;
	bool	quotes;
	char	**argv;
	char	**env;
}	t_minishell;

#endif
