/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:28:47 by allblue           #+#    #+#             */
/*   Updated: 2024/04/12 11:58:18 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

/*		REMOVE		*/
void	ft_print_token_list(t_token *list);
void	ft_print_arg_list(t_arg *list);
void	ft_print_cmd_list(t_cmd *list);

/*		EXEC		*/
int			ft_exec(t_data *data, t_cmd *cmd);
int			ft_fork(t_data *data);
void		ft_wait_for_children(t_data *data);
void		ft_launch_exec(t_data *data);

/*		EXEC_UTILS	*/
void		ft_close_pipes(t_data *data);
int			alloc_ids(t_data *data);
int			alloc_pipes(t_data *data);
int			is_infile(t_cmd *cmd);
char		*get_missing_file(t_infile *inf_list);
char		*get_last_infile(t_infile *inf_list);
t_outfile	*get_last_outfile(t_outfile *out_list);
char		*ft_get_cmd_path(char *cmd_name);
void		cmd_not_found_error(char *cmd_name);

/*		HEREDOCS	*/
char		*get_file_name(int i);
void		writing_loop(t_data *data, int fd_hd, char *delimiter, bool to_expand);
int			do_heredocs(t_data *data);
int			ft_launch_heredoc(t_data *data);

/*		BUILTINS	*/
int			ft_pwd(t_arg *arg_list);
int			ft_exec_builtin(t_data *data, t_cmd *cmd);
char		*ft_getcwd(void);
int			ft_change_dir(t_cmd *cmd);
int			ft_echo(t_cmd *cmd);

/*		BUILTIN_UTILS	*/
int			ft_isbuiltin(t_cmd *cmd);

/*		HD_COUNT		*/
int			get_err_pos(t_cmd *cmd);
int			count_hd_pre_error(t_cmd *cmd);
int			count_heredocs(t_infile *inf_list);
int			get_hd_number(t_cmd *list);

/*		MULTI_CMDS		*/
void		first_cmd(t_data *data, t_cmd *cmd_to_exec);
void		middle_cmd(t_data *data, t_cmd *cmd_to_exec, int process);
void		last_cmd(t_data *data, t_cmd *cmd_to_exec, int process);
void		child_process(t_data *data, int process);
int			ft_init_pipes(t_data *data);

/*		SINGLE_CMD		*/
char		*ft_get_valid_infile(t_data *data, t_cmd *cmd);
int			ft_get_fd_in(t_data *data, t_cmd *cmd);
int			ft_get_fd_out(t_data *data, t_cmd *cmd);
void		ft_exec_single_cmd(t_data *data);

#endif