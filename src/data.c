/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:30:56 by momrane           #+#    #+#             */
/*   Updated: 2024/04/18 11:42:20 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// static void	ft_init_data(t_data *data, char **env)
// {
// 	data->line = NULL;
// 	data->env = env;
// 	data->cmd_list = NULL;
// 	data->token_list = NULL;
// 	data->cmd_nb = 0;
// 	data->hdnum = 0;
// 	data->fd_hd = NULL;
// 	data->hd_files = NULL;
// 	data->ids = NULL;
// 	data->pipe_ends = NULL;
// 	data->path_list = ft_split(getenv("PATH"), ':'); //on ne protège pas le split ici?
// 	data->join_path = NULL;
// 	data->step = 0;
// 	data->env_list = ft_create_env_list(env);
// 	if (!data->env_list)
// 		return (free(data), NULL);
// 	data->hd_pos = -1;
// 	data->exit_status = 0;
// 	data->exit_builtin = NO;
// }

t_data	*ft_create_data(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	ft_memset(data, 0, sizeof(t_data));
	data->line = NULL;
	data->env = env;
	data->cmd_list = NULL;
	data->token_list = NULL;
	data->cmd_nb = 0;
	data->hdnum = 0;
	data->fd_hd = NULL;
	data->hd_files = NULL;
	data->ids = NULL;
	data->pipe_ends = NULL;
	data->path_list = ft_split(getenv("PATH"), ':'); //on ne protège pas le split ici?
	data->join_path = NULL;
	data->step = 0;
	data->env_list = ft_create_env_list(env);
	if (!data->env_list)
		return (free(data), NULL);
	data->hd_pos = -1;
	data->exit_status = 0;
	data->exit_builtin = NO;
	// ft_init_data(data, env);
	// data->line = NULL;
	// data->env = env;
	// data->cmd_list = NULL;
	// data->token_list = NULL;
	// data->cmd_nb = 0;
	// data->hdnum = 0;
	// data->fd_hd = NULL;
	// data->hd_files = NULL;
	// data->ids = NULL;
	// data->pipe_ends = NULL;
	// data->path_list = ft_split(getenv("PATH"), ':');
	// data->join_path = NULL;
	// data->step = 0;
	// data->env_list = ft_create_env_list(env);
	// data->hd_pos = -1;
	// data->exit_status = 0;
	// data->exit_builtin = NO;
	// if (!data->env_list)
	// 	return (free(data), NULL);
	ft_setup_signals(data);
	return (data);
}
