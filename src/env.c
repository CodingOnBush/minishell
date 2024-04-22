/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:49:21 by allblue           #+#    #+#             */
/*   Updated: 2024/04/21 18:54:29 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_env	*ft_new_env(char *key, char *value)
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

static t_env	*ft_str_to_env(char *line)
{
	t_env	*new_env;
	char	*value;
	char	*equal;
	char	*key;

	equal = ft_strchr(line, '=');
	if (!equal)
		return (NULL);
	key = ft_substr(line, 0, equal - line);
	if (!key)
		return (NULL);
	value = ft_strdup(equal + 1);
	if (!value)
		return (free(key), NULL);
	new_env = ft_new_env(key, value);
	if (!new_env)
		return (free(key), free(value), NULL);
	return (new_env);
}

static void	ft_add_new_env(t_env **env_list, t_env *new)
{
	t_env	*cur;

	if (!*env_list)
	{
		*env_list = new;
		return ;
	}
	cur = *env_list;
	while (cur->next)
		cur = cur->next;
	cur->next = new;
}

t_env	*ft_create_envlist(char **env)
{
	t_env	*res;
	t_env	*new;
	int		i;

	res = NULL;
	i = 0;
	while (env[i])
	{
		new = ft_str_to_env(env[i]);
		if (!new)
			return (NULL);
		ft_add_new_env(&res, new);
		i++;
	}
	return (res);
}

void	ft_free_env_list(t_env **env_list)
{
	t_env	*cur;
	t_env	*next;

	cur = *env_list;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur->key);
		free(cur->value);
		free(cur);
		cur = next;
	}
	*env_list = NULL;
}
