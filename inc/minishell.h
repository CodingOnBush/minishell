/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:20 by momrane           #+#    #+#             */
/*   Updated: 2024/04/03 15:09:33 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "includes.h"
#include "defines.h"
#include "structs.h"

#include "init.h"
#include "lexer.h"
#include "parser.h"

/*		EXEC		*/
void	ft_start_exec(t_data *data);

/*		FREE			*/
void 	ft_free_path(char **path);
void 	ft_free_arg_list(t_arg **arg_list);
void 	ft_free_infile_list(t_infile **infile_list);
void 	ft_free_outfile_list(t_outfile **outfile_list);
void 	ft_free_tokens(t_token **list);
void 	ft_free_cmds(t_cmd **cmd_list);
void 	ft_free_lexing_and_parsing(t_data *data);
void 	unlink_and_free(t_data *data, char **hd_files);

/*		REMOVE		*/
char	*ft_type_to_str(int type);
void	ft_print_token_list(t_token *list);
void	ft_print_arg_list(t_arg *list);
void	ft_print_cmd_list(t_cmd *list);

/*		UTILS		*/
int 	ft_isspace(char c);
int 	ft_isquote(char c);
int 	ft_isappend(char *str);
int 	ft_isheredoc(char *str);
int 	ft_isop(char *str);
int 	ft_get_type(char *str);
char 	*ft_strndup(char *s, int n);
int 	ft_isoperator(char *str);
t_token	*ft_findlast_token(t_token *lst);
char 	*ft_type_to_str(int type);
int 	ft_get_pipe_count(t_token *token_list);

/*		BUILTINS	*/
char 	*ft_getcwd(void);

/*		HD_COUNT	*/
int 	get_err_pos(t_cmd *cmd);
int 	count_hd_pre_error(t_cmd *cmd);
int 	count_heredocs(t_infile *inf_list);
int 	get_hd_number(t_cmd *list);

/*		HEREDOCS	*/
int 	do_heredocs(t_data *data);

/*		UTILS_LIBFT	*/
char	*ft_strndup(char *s, int n);
char	*ft_super_strjoin(char *new_str, char *toadd);
int		ft_isspace(char c);
int		ft_isquote(char c);
int		ft_is_in_var(char c);

#endif