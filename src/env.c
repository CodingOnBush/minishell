/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:49:21 by allblue           #+#    #+#             */
/*   Updated: 2024/04/19 11:57:13 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*ft_create_env_list(char **env)
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

// char	*ft_getenv(t_env *env_list, char *key)
// {
// 	t_env	*tmp;

// 	tmp = env_list;
// 	while (tmp)
// 	{
// 		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
// 			return (ft_strdup(tmp->value));
// 		tmp = tmp->next;
// 	}
// 	return (NULL);
// }

// void	ft_remove_env(t_env **env_list, char *key)
// {
// 	t_env	*tmp;
// 	t_env	*prev;

// 	tmp = *env_list;
// 	prev = NULL;
// 	while (tmp)
// 	{
// 		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
// 		{
// 			if (prev)
// 				prev->next = tmp->next;
// 			else
// 				*env_list = tmp->next;
// 			free(tmp->key);
// 			free(tmp->value);
// 			free(tmp);
// 			return ;
// 		}
// 		prev = tmp;
// 		tmp = tmp->next;
// 	}
// }

t_env	*ft_create_new_var(char *key, char *value)
{
	t_env	*new_var;

	new_var = malloc(sizeof(t_env));
	if (!new_var)
		return (NULL);
	new_var->key = ft_strdup(key);
	if (!new_var->key)
		return (free(new_var), NULL);
	new_var->value = ft_strdup(value);
	if (!new_var->value)
		return (free(new_var->key), free(new_var), NULL);
	new_var->next = NULL;
	return (new_var);
}

void	ft_update_env(t_env **env_list, char *key, char *new)
{
	t_env	*tmp;

	tmp = *env_list;
	if (!new)
		return ;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(new);
			return ;
		}
		tmp = tmp->next;
	}
}


static int	ft_get_env_size(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

// void	ft_add_new_env_var(t_data *data, char *var_name, char *var_value)
// {
// 	char	**new_env;
// 	char	*tmp;
// 	int		i;

// 	new_env = (char **)malloc(sizeof(char *) * (ft_get_env_size(data->env) + 2));
// 	if (!new_env)
// 	{
// 		data->exit_status = 1;
// 		return ;
// 	}
// 	i = 0;
// 	while (data->env[i])
// 	{
// 		new_env[i] = ft_strdup(data->env[i]);
// 		i++;
// 	}
// 	tmp = ft_strjoin(var_name, "=");
// 	new_env[i] = ft_strjoin(tmp, var_value);
// 	free(tmp);
// 	new_env[i + 1] = NULL;
// 	ft_free_env(data->env);
// 	data->env = new_env;
// }

void	ft_print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		ft_putstr_fd(env[i], 1);
		i++;
	}
}
