/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:20 by momrane           #+#    #+#             */
/*   Updated: 2024/03/14 11:44:20 by momrane          ###   ########.fr       */
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

# define SUCCESS 1
# define FAIL 0

# define DOUBLE_QUTOES '\"'
# define SINGLE_QUOTE '\''

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

/*		FREE		*/
void				ft_free_tokens(t_token **list);

/*		UTILS		*/
int					ft_isspace(char c);
int					ft_isoperator(char *str);
int					ft_isword(char c);
char				*ft_strndup(const char *s, int n);
void				print_list(t_token *list);
t_token				*ft_findlast(t_token *lst);

/*		TOKEN		*/
t_token				*ft_create_token(char *value, char *type);
void				ft_add_token(t_token **token_list, char *value);
int					ft_add_new_token(t_token **token_list, char *line);
t_token				*ft_create_token_list(char *line);

#endif