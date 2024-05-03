/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:31:29 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 12:41:22 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/*			BUILTINS	*/
int			ft_isbuiltin(t_cmd *cmd);
int			ft_exec_builtin(t_data *data, t_cmd *cmd);

/*			ENV_UTILS	*/
int			ft_setenv(t_env **env_list, char *key, char *value);
void		ft_remove_env(t_env **env_list, char *key);
char		*ft_getenv(t_env *env_list, char *key);
int			ft_print_env(t_data *data);

/*			EXEC_UTILS	*/
char		*ft_get_cmd_path(t_data *data, char *cmd_name);
char		**ft_create_env(t_data *data);

/*			EXEC_UTILS2	*/
void		ft_special_check(t_data *data, char *str);

/*		EXEC		*/
int			ft_isdirectory(char *path);
int			ft_execve(t_data *data, t_cmd *cmd);
void		ft_launch_exec(t_data *data);

/*			FT_CD			*/
int			ft_cd(t_env *env_list, t_cmd *cmd);

/*			FT_ECHO			*/
int			ft_echo(t_data *data, t_cmd *cmd);

/*		FT_EXIT			*/
int			ft_exit(t_data *data, t_arg *arg_list);

/*		FT_EXPORT_UTILS	*/
void		ft_add_new_exp(t_env **exp_list, t_env *new);
t_env		*ft_create_default_exp(void);
t_env		*ft_create_explist(char **env);
void		ft_print_exports_var(t_data *data);
void		ft_remove_exp(t_env **exp_list, char *key);

/*		FT_EXPORT_UTILS2	*/
int			ft_add_exp(t_env **exp_list, char *base, char *key, char *value);

/*		FT_EXPORT_UTILS3	*/
int			ft_handle_line(t_data *data, char *line);

/*		FT_EXPORT		*/
int			ft_export(t_data *data, t_cmd *cmd);

/*			GET_REDIRS		*/
t_redir		*ft_get_redirs(t_data *data, t_cmd *cmd);

/*			HD_COUNT		*/
int			ft_get_hd_nb(t_cmd *list);

/*			HEREDOCS_UTILS	*/
int			ft_is_error_to_print(t_token *list);
t_infile	*ft_get_next_infile(t_infile *infile, char *name);
void		ft_set_heredoc_files(t_data *data);

/*			HEREDOCS_UTILS2	*/
char		**ft_create_hd_filenames(int hdnum);

/*			HEREDOCS		*/
int			ft_launch_heredoc(t_data *data);

/*			MULTI CMDS UTILS	*/
void		ft_close_fd_pipes(t_data *data, t_redir *redir);
void		ft_exit_if_null(t_data *data, t_redir *redir);

/*			MULTI_CMDS			*/
void		ft_child_process(t_data *data, int process);

/*			PIPE			*/
void		ft_close_pipes(t_data *data);
int			**ft_create_pipe_ends(int pipe_nb);

/*			SINGLE_CMD		*/
void		ft_exec_single_cmd(t_data *data);

/*			SINGLE_CMD_BUILTIN	*/
int			ft_exec_single_builtin(t_data *data);

#endif