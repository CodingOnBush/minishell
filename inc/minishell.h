/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:20 by momrane           #+#    #+#             */
/*   Updated: 2024/03/13 15:04:34 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>

# define YES 1
# define NO 0

# define DQ '\"'

typedef struct s_token
{
	char			*value;
	char			*type;
	struct s_token	*next;
}					t_token;

typedef struct s_data
{
	char			*line;
	t_token			*token_list;
}					t_data;

/*		UTILS		*/
int					ft_isspace(char c);
int					ft_isoperator(char *str);

#endif