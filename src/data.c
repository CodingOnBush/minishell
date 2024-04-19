/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:30:56 by momrane           #+#    #+#             */
/*   Updated: 2024/04/19 11:59:32 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	**ft_duplicate_env(char **env)
{
	char	**res;
	int		i;

	i = 0;
	while (env[i])
		i++;
	res = malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (env[i])
	{
		res[i] = ft_strdup(env[i]);
		if (!res[i])
			return (ft_free_args(&res), NULL);
		i++;
	}
	res[i] = NULL;
	return (res);
}

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
	data->env = ft_duplicate_env(env);
	if (!data->env)
		return (free(data), NULL);
	data->cmd_list = NULL;
	data->token_list = NULL;
	data->cmd_nb = 0;
	data->hdnum = 0;
	data->fd_hd = NULL;
	data->hd_files = NULL;
	data->ids = NULL;
	data->pipe_ends = NULL;
	data->path_list = ft_split(ft_getenv(data->env_list, "PATH"), ':');
	data->join_path = NULL;
	data->step = 0;
	data->env_list = ft_create_env_list(env);
	if (!data->env_list)
		return (free(data), NULL);
	data->hd_pos = -1;
	data->exit_status = 0;
	data->exit_builtin = NO;
	ft_setup_signals(data);
	return (data);
}
