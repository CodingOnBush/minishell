/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:30:56 by momrane           #+#    #+#             */
/*   Updated: 2024/04/19 15:34:28 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// static char	**ft_duplicate_env(char **env)
// {
// 	char	**res;
// 	int		i;

// 	i = 0;
// 	while (env[i])
// 		i++;
// 	res = malloc(sizeof(char *) * (i + 1));
// 	if (!res)
// 		return (NULL);
// 	i = 0;
// 	while (env[i])
// 	{
// 		res[i] = ft_strdup(env[i]);
// 		if (!res[i])
// 			return (ft_free_args(&res), NULL);
// 		i++;
// 	}
// 	res[i] = NULL;
// 	return (res);
// }

static char	*ft_get_key(char *str)
{
	char	*equal;

	equal = ft_strchr(str, '=');
	if (!equal)
		return (NULL);
	return (ft_substr(str, 0, equal - str));
}

static char	*ft_get_value(char *str)
{
	char	*equal;

	equal = ft_strchr(str, '=');
	if (!equal)
		return (NULL);
	return (ft_strdup(equal + 1));
}

static t_env	*ft_new_env(char *line)
{
	t_env	*new_env;

	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = ft_get_key(line);
	if (!new_env->key)
		return (free(new_env), NULL);
	new_env->value = ft_get_value(line);
	if (!new_env->value)
		return (free(new_env->key), free(new_env), NULL);
	new_env->next = NULL;
	return (new_env);
}

static t_env	*ft_create_env_list(char **env)
{
	t_env	*res;
	t_env	*new;
	int		i;

	res = NULL;
	i = 0;
	while (env[i])
	{
		new = ft_new_env(env[i]);
		if (!new)
			return (NULL);
		ft_add_new_env(&res, new);
		i++;
	}
	return (res);
}

t_data *const	ft_create_data(int ac, char **av, char **env)
{
	t_data *const	data = malloc(sizeof(t_data));

	(void)ac;
	(void)av;
	if (!data)
		return (NULL);
	ft_memset(data, 0, sizeof(t_data));
	data->env = env;// to remove
	data->line = NULL;
	data->cmd_list = NULL;
	data->token_list = NULL;
	data->cmd_nb = 0;
	data->hdnum = 0;
	data->fd_hd = NULL;
	data->hd_files = NULL;
	data->ids = NULL;
	data->pipe_ends = NULL;
	data->join_path = NULL;
	data->step = 0;
	data->env_list = ft_create_env_list(env);
	data->hd_pos = -1;
	data->exit_status = 0;
	data->exit_builtin = NO;
	ft_setup_signals(data);
	return (data);
}
