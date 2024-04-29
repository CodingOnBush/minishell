/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 01:49:21 by allblue           #+#    #+#             */
/*   Updated: 2024/04/29 14:07:05 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*ft_new_env(char *key, char *value)
{
	t_env	*new;

	if (!key || !value)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
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

static t_env	*ft_create_default_env(void)
{
	t_env	*new;
	t_env	*res;

	res = NULL;
	new = ft_new_env(ft_strdup("PWD"), getcwd(NULL, 0));
	if (!new)
		return (NULL);
	ft_add_new_env(&res, new);
	new = ft_new_env(ft_strdup("SHLVL"), ft_strdup("1"));
	if (!new)
		return (ft_free_env_list(&res), NULL);
	ft_add_new_env(&res, new);
	new = ft_new_env(ft_strdup("_"), ft_strdup("/usr/bin/env"));
	if (!new)
		return (ft_free_env_list(&res), NULL);
	ft_add_new_env(&res, new);
	return (res);
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
			return (ft_free_env_list(&res), NULL);
		ft_add_new_env(&res, new);
		i++;
	}
	if (res == NULL)
		res = ft_create_default_env();
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
		if (cur->key)
			free(cur->key);
		if (cur->value)
			free(cur->value);
		free(cur);
		cur = next;
	}
	*env_list = NULL;
}
