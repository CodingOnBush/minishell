/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 02:04:51 by allblue           #+#    #+#             */
/*   Updated: 2024/04/07 14:33:50 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_get_key(char *str)
{
	char	*equal;

	equal = ft_strchr(str, '=');
	if (!equal)
		return (NULL);
	return (ft_substr(str, 0, equal - str));
}

char	*ft_get_value(char *str)
{
	char	*equal;

	equal = ft_strchr(str, '=');
	if (!equal)
		return (NULL);
	return (ft_strdup(equal + 1));
}

t_env	*ft_new_env(char *line)
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

void	ft_add_new_env(t_env **env_list, t_env *new_env)
{
	t_env	*tmp;

	if (!*env_list)
	{
		*env_list = new_env;
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new_env;
}
