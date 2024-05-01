/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:28:47 by allblue           #+#    #+#             */
/*   Updated: 2024/05/01 11:06:23 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/*		BUILTINS	*/
int		ft_isbuiltin(t_cmd *cmd);
int		ft_exec_builtin(t_data *data, t_cmd *cmd);

/*		ENV_UTILS	*/
int		ft_setenv(t_env **env_list, char *key, char *value);
void	ft_remove_env(t_env **env_list, char *key);
char	*ft_getenv(t_env *env_list, char *key);
int		ft_key_exist(t_env *env_list, char *key);

/*		EXEC_UTILS	*/
char	*ft_get_cmd_path(t_data *data, char *cmd_name);
char	**ft_create_env(t_data *data);

/*		EXEC		*/
int		ft_execve(t_data *data, t_cmd *cmd);
void	ft_launch_exec(t_data *data);

/*		FT_CD			*/
int		ft_cd(t_env *env_list, t_cmd *cmd);

/*		FT_ECHO			*/
int		ft_echo(t_data *data, t_cmd *cmd);

/*		FT_EXIT			*/
int		ft_exit(t_data *data, t_arg *arg_list);

/*		FT_EXPORT_UTILS	*/
void	ft_add_new_exp(t_env **exp_list, t_env *new);
t_env	*ft_create_explist(char **env);
void	ft_print_exports_var(t_data *data);

/*		FT_EXPORT		*/
void	ft_remove_exp(t_env **exp_list, char *key);
int		ft_export(t_data *data, t_cmd *cmd);

/*		GET_REDIRS		*/
t_redir	*ft_get_redirs(t_data *data, t_cmd *cmd);

/*		HD_COUNT		*/
int		ft_get_hd_nb(t_cmd *list);

/*		HEREDOCS_UTILS	*/
char	**ft_create_hd_filenames(int hdnum);
char	*get_file_name(int i);
int		is_error_to_print(t_token *list);

/*		HEREDOCS		*/
int		ft_launch_heredoc(t_data *data);

/*		MULTI CMDS UTILS	*/
void	ft_close_fd_pipes(t_data *data, t_redir *redir);
void	ft_exit_if_null(t_data *data, t_redir *redir);

/*		MULTI_CMDS			*/
void	first_cmd(t_data *data, t_cmd *cmd_to_exec);
void	middle_cmd(t_data *data, t_cmd *cmd_to_exec, int process);
void	last_cmd(t_data *data, t_cmd *cmd_to_exec, int process);
void	ft_child_process(t_data *data, int process);

/*		PIPE			*/
void	ft_close_pipes(t_data *data);
int		**ft_create_pipe_ends(int pipe_nb);

/*	SINGLE_CMD_UTILS	*/
int		ft_get_fd_out(t_data *data, t_cmd *cmd);

/*		SINGLE_CMD		*/
int		ft_get_fd_in(t_data *data, t_cmd *cmd);
void	ft_exec_single_cmd(t_data *data);

/*		SINGLE_CMD_BUILTIN	*/
int		ft_exec_single_builtin(t_data *data);

#endif