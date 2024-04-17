/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:48:28 by momrane           #+#    #+#             */
/*   Updated: 2024/04/17 20:58:44 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_add_new_env(t_env **env_list, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (!*env_list)
	{
		*env_list = new;
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

t_env	*ft_env_to_env_list(char **env)
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

char	**ft_env_list_to_env(t_env *env_list)
{
	char	**res;
	t_env	*tmp;
	int		i;

	tmp = env_list;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	res = (char **)malloc(sizeof(char *) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	tmp = env_list;
	while (tmp)
	{
		res[i] = ft_strjoin_key_value(tmp->key, tmp->value);
		i++;
		tmp = tmp->next;
	}
	res[i] = NULL;
	return (res);
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

int	ft_update_var(t_env **env_list, char *key, char *value)
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

int	ft_add_new_env_var(t_env **env_list, char *key, char *value)
{
	t_env	*new;

	new = ft_create_new_var(key, value);
	if (!new)
		return (FAIL);
	ft_add_new_env(env_list, new);
	return (SUCCESS);
}

char	*ft_strjoin_key_value(char *key, char *value)
{
	char	*res;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	res = ft_strjoin(tmp, value);
	free(tmp);
	return (res);
}

char	*ft_extract_key(char*str)
{
	int		i;
	char	*res;

	if (ft_strchr(str, '=') == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_extract_value(char *str)
{
	int		i;
	int		j;
	char	*res;

	if (ft_strchr(str, '=') == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (NULL);
	i++;
	j = 0;
	while (str[i + j])
		j++;
	res = (char *)malloc(sizeof(char) * (j + 1));
	if (!res)
		return (NULL);
	j = 0;
	while (str[i + j])
	{
		res[j] = str[i + j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

void	ft_add_new_env_in_list(t_env **env_list, char *key, char *value)
{
	t_env	*new_var;

	new_var = ft_create_new_var(key, value);
	if (!new_var)
	{
		ft_free_env_list(env_list);
		*env_list = NULL;
		return ;
	}
	ft_add_new_env(env_list, new_var);
}
