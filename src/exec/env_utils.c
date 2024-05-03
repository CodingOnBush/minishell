/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:31:56 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 12:31:57 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_update_var(t_env **env_list, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			if (tmp->value)
				free(tmp->value);
			tmp->value = value;
			if (key)
				free(key);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	return (FAIL);
}

int	ft_setenv(t_env **env_list, char *key, char *value)
{
	t_env	*new;
	t_env	*tmp;

	if (!key || !value)
		return (SUCCESS);
	if (ft_update_var(env_list, key, value) == SUCCESS)
		return (SUCCESS);
	new = ft_new_env(NULL, key, value);
	if (!new)
		return (FAIL);
	if (!*env_list)
		*env_list = new;
	else
	{
		tmp = *env_list;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
	return (SUCCESS);
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
			if (tmp->key)
				free(tmp->key);
			if (tmp->value)
				free(tmp->value);
			if (tmp->base)
				free(tmp->base);
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
		if (ft_strcmp(tmp->key, key) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

int	ft_print_env(t_data *data)
{
	t_env	*env_list;

	if (!data)
		return (1);
	env_list = data->env_list;
	while (env_list)
	{
		ft_putstr_fd(env_list->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(env_list->value, 1);
		ft_putstr_fd("\n", 1);
		env_list = env_list->next;
	}
	return (0);
}
