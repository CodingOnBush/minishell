/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:01:50 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 11:11:04 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

t_env	*ft_new_env(char *str, char *key, char *value)
{
	t_env	*new;

	if (!key)
		return (NULL);
	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->base = str;
	new->key = key;
	new->value = value;
	new->next = NULL;
	return (new);
}

t_env	*ft_str_to_env(char *line)
{
	t_env	*new_env;
	char	*value;
	char	*equal;
	char	*key;
	char	*base;

	equal = ft_strchr(line, '=');
	if (!equal)
		return (NULL);
	key = ft_substr(line, 0, equal - line);
	if (!key)
		return (NULL);
	value = ft_strdup(equal + 1);
	if (!value)
		return (free(key), NULL);
	base = ft_strdup(line);
	if (!base)
		return (free(key), free(value), NULL);
	new_env = ft_new_env(base, key, value);
	if (!new_env)
		return (free(key), free(value), free(base), NULL);
	return (new_env);
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
		if (cur->base)
			free(cur->base);
		free(cur);
		cur = next;
	}
	*env_list = NULL;
}
