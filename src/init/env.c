/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:32:15 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 12:32:16 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

t_env	*ft_create_new_env(char *base, char *key, char *value)
{
	t_env	*new;
	char	*newkey;
	char	*newvalue;
	char	*newbase;

	newkey = ft_strdup(key);
	if (!newkey)
		return (NULL);
	newvalue = ft_strdup(value);
	if (!newvalue)
		return (free(newkey), NULL);
	newbase = ft_strdup(base);
	if (!newbase)
		return (free(newkey), free(newvalue), NULL);
	new = ft_new_env(newbase, newkey, newvalue);
	if (!new)
		return (free(newkey), free(newvalue), free(newbase), NULL);
	return (new);
}

t_env	*ft_create_default_env(void)
{
	t_env	*new;
	t_env	*res;

	res = NULL;
	new = ft_create_new_env(NULL, "PWD", getcwd(NULL, 0));
	if (!new)
		return (ft_free_env_list(&res), NULL);
	ft_add_new_env(&res, new);
	new = ft_create_new_env(NULL, "SHLVL", "1");
	if (!new)
		return (ft_free_env_list(&res), NULL);
	ft_add_new_env(&res, new);
	new = ft_create_new_env(NULL, "_", "/usr/bin/env");
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
