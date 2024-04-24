/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:28:47 by allblue           #+#    #+#             */
/*   Updated: 2024/04/24 12:40:25 by vvaudain         ###   ########.fr       */
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

/*		ENV			*/
t_env	*ft_new_env(char *key, char *value);
t_env	*ft_create_envlist(char **env);
void	ft_free_env_list(t_env **env_list);

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

/*		FT_EXPORT		*/
int		ft_export(t_data *data, t_cmd *cmd);

/*		GET_REDIRS		*/
t_redir	*ft_get_redirs(t_data *data, t_cmd *cmd);

/*		HD_COUNT		*/
int		get_hd_number(t_cmd *list);

/*		HEREDOCS	*/
int		ft_launch_heredoc(t_data *data);

/*		MULTI_CMDS		*/
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