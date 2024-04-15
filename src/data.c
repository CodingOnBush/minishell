/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:30:56 by momrane           #+#    #+#             */
/*   Updated: 2024/04/15 09:53:55 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_init_data(t_data *data, char **env)
{
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
	data->hd_pos = -1;
	data->exit_status = 0;
	data->exit_builtin = NO;
	if (!data->env_list)
		return (free(data), NULL);
}

t_data	*ft_create_data(char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	ft_memset(data, 0, sizeof(t_data));
	ft_init_data(data, env);
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
