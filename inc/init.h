/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:38:17 by momrane           #+#    #+#             */
/*   Updated: 2024/04/07 15:31:06 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

/*		DATA		*/
t_data	*ft_create_data(char **env);

/*		SIGNALS		*/
void	ft_setup_signals(t_data *data);

/*		UTILS		*/
int 	ft_isappend(char *str);
int 	ft_isheredoc(char *str);
int 	ft_isop(char *str);
int 	ft_get_type(char *str);
int 	ft_isoperator(char *str);
int 	ft_get_pipe_count(t_token *token_list);
char	*ft_strndup(char *s, int n);
char	*ft_super_strjoin(char *new_str, char *toadd);
int 	ft_isspace(char c);
int 	ft_isquote(char c);
int		ft_is_in_var(char c);

/*		ENV			*/
t_env	*ft_create_env_list(char **env);
char	*ft_get_env_value(t_env *env_list, char *key);
void	ft_remove_env(t_env **env_list, char *key);
t_env	*ft_create_new_var(char *key, char *value);

/*		ENV_UTILS	*/
char	*ft_get_key(char *str);
char	*ft_get_value(char *str);
t_env	*ft_new_env(char *line);
void	ft_add_new_env(t_env **env_list, t_env *new_env);

/*		FREE		*/
void	ft_free_tokens(t_token **token_list);
void	ft_free_arg_list(t_arg **arg_list);
void	ft_free_infiles(t_infile **infile_list);
void	ft_free_outfiles(t_outfile **outfile_list);
void	ft_free_args(char ***args);
void	ft_free_cmd(t_cmd *cmd);
void	ft_free_path(char **path);
void	ft_free_infile_list(t_infile **infile_list);
void	ft_free_outfile_list(t_outfile **outfile_list);
void	ft_free_cmd_list(t_cmd **cmd_list);
void	ft_free_lexing_and_parsing(t_data *data);
void	unlink_and_free(t_data *data);
void	ft_free_exec(t_data *data);
void	ft_free_pipe_ends(t_data *data);
void	ft_free_all(t_data *data);
void	ft_free_hd_files(t_data *data);
void	ft_reset_data(t_data *data);
void	ft_free_env_list(t_env **env_list);


#endif