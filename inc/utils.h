/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/22 17:37:36 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 12:42:38 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

/*		FREE_UTILS		*/
void	ft_free_cmd_list(t_cmd **cmd_list);
void	ft_free_tokens(t_token **token_list);
void	ft_free_env(char **env);

/*		FREE			*/
void	ft_reset_data(t_data *data);
void	ft_free_all(t_data *data);

/*		UTILS			*/
int		ft_isop(char *str);
int		ft_gettype(char *str);
int		ft_isoperator(char *str);
char	*ft_strndup(char *s, int n);
char	*ft_super_strjoin(char *new_str, char *toadd);
int		ft_is_space(char c);
int		ft_isquote(char c);
int		ft_is_in_var(char c);
int		ft_strcmp(char *s1, char *s2);
int		ft_get_env_list_size(t_env *env);
int		ft_get_arg_list_size(t_arg *arg_list);
int		ft_file_is_append(t_cmd *cmd, char *filename);
void	ft_print_and_exit(t_data *data, int status);

#endif