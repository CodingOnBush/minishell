/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:20 by momrane           #+#    #+#             */
/*   Updated: 2024/03/20 11:32:18 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdbool.h>

# define MINISPELL "minispell > "

# define YES 1
# define NO 0

# define SUCCESS 1
# define FAIL -1
// # define ERROR -1

# define DOUBLE_QUOTES '\"'
# define SINGLE_QUOTE '\''

# define HERE_DOC 1
# define APPEND 2
# define PIPE 3
# define LEFT_TRUNC 4
# define RIGHT_TRUNC 5
# define WORD 6

typedef struct s_infile
{
	char				*infile;
	bool				here_doc;
	char				*delimiter; //null si pas de here_doc
	struct s_infile		*next;
}						t_infile;

typedef struct s_outfile
{
	char				*outfile;
	bool				append;
	struct s_outfile	*next;
}						t_outfile;

typedef struct s_arg
{
	char			*value;
	struct s_arg	*next;
}					t_arg;

typedef struct s_cmd
{
	t_arg				*args;
	t_infile			*infile;
	t_outfile			*outfile;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_token
{
	char				*value;
	int					type;
	struct s_token		*next;
}						t_token;

typedef struct s_data
{
	int					ac;
	char				**av;
	char				**env;
	char				**path;
	char				*line;
	t_cmd				*cmd_list;
	t_token				*token_list;
	struct sigaction	sigint_action;
	struct sigaction	sigquit_action;
}						t_data;

/*		SIGNALS		*/
void					ft_setup_signals(t_data *data);

/*		FREE		*/
void					ft_free_tokens(t_token **list);
void					ft_free_path(char **path);

/*		UTILS		*/
int						ft_isspace(char c);
int						ft_isoperator(char *str);
int						ft_isword(char c);
char					*ft_strndup(const char *s, int n);
void					print_list(t_token *list);
t_token					*ft_findlast(t_token *lst);
int						ft_isappend(char *str);
int						ft_isheredoc(char *str);
int						ft_isredirection(char *str);
void					ft_set_path(t_data *data);

/*		TOKENS		*/
t_token					*ft_create_token(char *value);
void					ft_add_token(t_token **token_list, char *value);
int						ft_add_new_token(t_token **token_list, char *line);
t_token					*ft_create_token_list(char *line);

/*		TOKEN CHECK		*/
int						check_token_list(t_token *list);

/*		ARGS		*/
int						add_new_arg(t_arg *head, char *value);

/*		PARSING		*/
int						ft_parse_commands(t_data *data);

#endif