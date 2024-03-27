/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:20 by momrane           #+#    #+#             */
/*   Updated: 2024/03/27 17:15:04 by momrane          ###   ########.fr       */
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

# define MINISPELL "\001\e[1;38;5;141m\002minispell\001\e[1;33m\002 > \001\033[0m\002"

# define YES 1
# define NO 0

# define SUCCESS 1
# define FAIL -1

# define DOUBLE_QUOTES '\"'
# define SINGLE_QUOTE '\''

# define HERE_DOC 1
# define APPEND 2
# define PIPE 3
# define LEFT_TRUNC 4
# define RIGHT_TRUNC 5
# define WORD 6
# define NEWLINE_ERROR 7
# define QUOTES_ERROR 8
# define SINGLE_QUOTE_ERROR 9
# define DOUBLE_QUOTE_ERROR 10
# define QWORD 11
# define DOUBLE_PIPE_ERROR 12

typedef struct s_infile
{
	char				*filename;
	char				*delimiter;// null : pas HEREDOCdonc LC
	struct s_infile		*next;
}						t_infile;

typedef struct s_outfile
{
	char				*filename;
	bool				append;// false : RIGTH_TRUNC
	struct s_outfile	*next;
}						t_outfile;

typedef struct s_arg
{
	char				*value;
	struct s_arg		*next;
}						t_arg;

typedef struct s_token
{
	char				*str;
	int					type;
	bool				attributed;
	int					pos;
	bool				error;
	int					err_type;
	struct s_token		*next;
}						t_token;

typedef struct s_cmd
{
	t_token				*token_list;
	t_arg				*arg_list;// we can remove it thanks to token_list
	t_infile			*infile_list;
	t_outfile			*outfile_list;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_data
{
	int					ac;
	char				**av;
	char				**env;
	char				**path;
	char				*line;
	t_cmd				*cmd_list;
	t_token				*token_list;
	int					hdnum;
	t_token				*token_split;
	struct sigaction	sigint_action;
	struct sigaction	sigquit_action;
}						t_data;

/*		EXEC			*/
void					ft_start_exec(t_data *data);

/*		LEXER			*/
int						ft_start_lexing(t_data *data);

/*		INFILE			*/
t_infile				*ft_create_new_infile(char *str, int type);
void					ft_add_infile(t_infile **infile_list, t_infile *new_infile);

/*		OUTFILE			*/
t_outfile				*ft_create_new_outfile(char *filename, int type);
void					ft_add_outfile(t_outfile **outfile_list, t_outfile *new_outfile);

/*		SIGNALS			*/
void					ft_setup_signals(t_data *data);

/*		FREE			*/
void					ft_free_path(char **path);
void					ft_free_arg_list(t_arg **arg_list);
void					ft_free_infile_list(t_infile **infile_list);
void					ft_free_outfile_list(t_outfile **outfile_list);
void					ft_free_tokens(t_token **list);
void					ft_free_cmds(t_cmd **cmd_list);
void					ft_free_lexing_and_parsing(t_data *data);

/*		ERRORS			*/
void					assign_error(t_token *token, int err_type);
void					ft_error_messages(int errno);

/*		CHECK			*/
int						ft_check_quote_error(char *line);
int 					ft_check_double_pipe(t_token *token);

/*		PRINT			*/
void					ft_print_token_list(t_token *list);
void					ft_print_cmd_list(t_cmd *list);
void					ft_print_arg_list(t_arg *list);

/*		UTILS			*/
int						ft_isspace(char c);
int						ft_isquote(char c);
int						ft_isappend(char *str);
int						ft_isheredoc(char *str);
int						ft_isop(char *str);
int						ft_get_type(char *str);
char					*ft_strndup(char *s, int n);
int						ft_isoperator(char *str);
t_token					*ft_findlast_token(t_token *lst);
int						ft_set_path(t_data *data);
char					*ft_type_to_str(int type);
int						ft_get_pipe_count(t_token *token_list);


/*		TOKEN CHECK		*/
int						check_token_list(t_token **list);
int						ft_check_pipe_error(t_token *token_list);

/*		ARGS			*/
t_arg					*create_new_arg(char *value);
void					add_new_arg(t_arg **head, t_arg *new_arg);

/*		DATA			*/
t_data					*ft_create_data(int ac, char **av, char **env);
int						ft_finish_init_data(t_data *data);

/*		PARSING			*/
t_cmd					*ft_create_cmd_list(t_token *token_list);
int						ft_start_parsing(t_data *data);

/*		HEREDOCS		*/
int						do_heredocs(t_data *data);

/*		TOKEN			*/
t_token					*ft_create_new_token(char *new_str, int type, int pos);
t_token					*ft_create_token_list(char *line);
void					ft_addlast_token(t_token **token_list, t_token *new_token);

#endif