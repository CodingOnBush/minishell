/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 22:46:21 by allblue           #+#    #+#             */
/*   Updated: 2024/04/21 18:54:29 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_update_var(t_env **env_list, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	return (FAIL);
}

void	ft_setenv(t_env **env_list, char *key, char *value)
{
	t_env	*new;
	t_env	*tmp;

	if (ft_update_var(env_list, key, value) == SUCCESS)
		return ;
	new = ft_new_env(key, value);
	if (!new)
		return ;
	if (!*env_list)
		*env_list = new;
	else
	{
		tmp = *env_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_remove_env(t_env **env_list, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env_list;
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env_list = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

char	*ft_getenv(t_env *env_list, char *key)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}
