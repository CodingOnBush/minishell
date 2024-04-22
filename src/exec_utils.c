/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:11:01 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/21 18:54:29 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	if (!path || !*path)
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
			return (ft_free_path(path_list), NULL); //ici il ne faut pas free sinon pas de path pour dire à l'exec que la cmd n'existe pas (booleen?)
		if (access(str, F_OK) == 0)
			return (ft_free_path(path_list), str);
		free(str);
		i++;
	}
	return (ft_free_path(path_list), NULL);
}

int	alloc_ids(t_data *data)
{
	data->ids = malloc(sizeof(int) * data->cmd_nb);
	if (!data->ids)
		return (perror("minishell: "), FAIL);
	return (SUCCESS);
}
