/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:11:01 by vvaudain          #+#    #+#             */
/*   Updated: 2024/05/01 17:08:21 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_create_cmd_path(char *path, char *cmd_name)
{
	char	*cmd_path;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	cmd_path = ft_strjoin(tmp, cmd_name);
	if (!cmd_path)
		return (NULL);
	free(tmp);
	return (cmd_path);
}

static void	ft_free_path(char **path)
{
	int	i;

	i = 0;
	if (!path)
		return ;
	while (path[i] != NULL)
	{
		free(path[i]);
		i++;
	}
	free(path);
}

char	*ft_get_cmd_path(t_data *data, char *cmd_name)
{
	char	**path_list;
	char	*str;
	int		i;

	if (cmd_name != NULL && *cmd_name == '\0')
		return (ft_strdup(""));
	if (ft_strchr(cmd_name, '/') != NULL)
		return (ft_strdup(cmd_name));
	str = ft_getenv(data->env_list, "PATH");
	path_list = ft_split(str, ':');
	if (!path_list)
		return (NULL);
	free(str);
	i = 0;
	while (path_list[i])
	{
		str = ft_create_cmd_path(path_list[i], cmd_name);
		if (!str)
			return (ft_free_path(path_list), NULL);
		if (access(str, F_OK) == 0)
			return (ft_free_path(path_list), str);
		free(str);
		i++;
	}
	return (ft_free_path(path_list), NULL);
}

static char	*ft_create_strenv(char *key, char *value)
{
	char	*str;

	str = ft_strjoin(key, "=");
	if (!str)
		return (NULL);
	value = ft_strjoin(str, value);
	if (!value)
		return (free(str), NULL);
	free(str);
	return (value);
}

char	**ft_create_env(t_data *data)
{
	char	**res;
	t_env	*cur;
	int		i;

	cur = data->env_list;
	if (!cur)
		return (NULL);
	i = ft_get_env_list_size(data->env_list);
	res = (char **)malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	cur = data->env_list;
	i = 0;
	while (cur)
	{
		res[i] = ft_create_strenv(cur->key, cur->value);
		if (!res[i])
			return (ft_free_env(res), NULL);
		cur = cur->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}
