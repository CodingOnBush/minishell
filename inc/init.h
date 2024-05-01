/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:38:17 by momrane           #+#    #+#             */
/*   Updated: 2024/05/01 20:02:47 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

/*		DATA		*/
void	ft_handle_no_double_prompt(int signum);
t_data	*ft_create_data(int ac, char **av, char **env);

/*		ENV			*/
t_env	*ft_create_new_env(char *base, char *key, char *value);
t_env	*ft_create_default_env(void);
t_env	*ft_str_to_env(char *line);
t_env	*ft_new_env(char *str, char *key, char *value);

/*		ENV_UTILS2	*/
t_env	*ft_create_envlist(char **env);
void	ft_free_env_list(t_env **env_list);

#endif