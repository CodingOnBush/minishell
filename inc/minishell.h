/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:20 by momrane           #+#    #+#             */
/*   Updated: 2024/04/06 18:38:57 by momrane          ###   ########.fr       */
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

/*		SINGLE EXEC		*/
char	*ft_get_valid_infile(t_data *data, t_cmd *cmd);
int		ft_get_fd_in(t_data *data, t_cmd *cmd);
int		ft_get_fd_out(t_data *data, t_cmd *cmd);
void	exec_single_command(t_data *data);

/*		MULTI CMDS		*/
void	first_cmd(t_data *data, t_cmd *cmd_to_exec);
void	middle_cmd(t_data *data, t_cmd *cmd_to_exec, int process);
void	last_cmd(t_data *data, t_cmd *cmd_to_exec, int process);
void	child_process(t_data *data, int process);
int		do_pipes(t_data *data);

/*		EXEC		*/
int		ft_exec(t_data *data, t_cmd *cmd);
void	exec_single_command(t_data *data);
int		ft_start_exec(t_data *data);

/*		FREE			*/
void 	ft_free_path(char **path);
void	ft_free_args(char ***args);
void 	ft_free_arg_list(t_arg **arg_list);
void 	ft_free_infile_list(t_infile **infile_list);
void 	ft_free_outfile_list(t_outfile **outfile_list);
void 	ft_free_tokens(t_token **list);
void 	ft_free_cmd_list(t_cmd **cmd_list);
void 	ft_free_lexing_and_parsing(t_data *data);
void 	unlink_and_free(t_data *data);
void	ft_free_exec(t_data *data);
void	ft_free_all(t_data *data);
void	ft_reset_data(t_data *data);
void	ft_free_infiles(t_infile **infile_list);
void	ft_free_cmd(t_cmd *cmd);
void	ft_free_outfiles(t_outfile **outfile_list);

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
char	**ft_create_args_array(t_arg *arg_list);

/*		BUILTINS	*/
char 	*ft_getcwd(void);
int		ft_exec_builtin(t_data *data, t_cmd *cmd);
int		ft_pwd(t_arg *arg_list);
int		ft_change_dir(t_cmd *cmd);
int		ft_echo(t_cmd *cmd);

/*		BUILTINS_UTILS	*/
int		ft_isbuiltin(char *cmd);

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

/*		EXEC_UTILS		*/
void	ft_close_pipes(t_data *data);
int		get_cmd_nb(t_cmd *cmd_list);
int		alloc_ids(t_data *data);
int		alloc_pipes(t_data *data);
void	set_cmd_pos(t_cmd *cmd_list);
int		is_infile(t_cmd *cmd);
char	*get_missing_file(t_infile *inf_list);
char	*get_last_infile(t_infile *inf_list);
t_outfile	*get_last_outfile(t_outfile *out_list);
char	*get_cmd_path(t_data *data, t_cmd *cmd);

#endif