/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 20:46:23 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 10:53:31 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_update_exp(t_env *prev, char *line, char *newvalue)
{
	if (prev->next->value)
	{
		free(prev->next->value);
		prev->next->value = newvalue;
	}
	if (prev->next->base)
	{
		free(prev->next->base);
		prev->next->base = line;
	}
	return (SUCCESS);
}

static void	ft_exp_link(t_env *prev, t_env *new, t_env **exp_list)
{
	if (prev != NULL)
	{
		if (new)
			new->next = prev->next;
		prev->next = new;
	}
	else
	{
		if (new)
			new->next = *exp_list;
		*exp_list = new;
	}
}

static t_env	*ft_get_right_exp(t_env *exp_list, char *key)
{
	t_env	*cur;
	t_env	*prev;

	prev = NULL;
	cur = exp_list;
	while (cur && ft_strcmp(cur->key, key) < 0)
	{
		prev = cur;
		cur = cur->next;
	}
	return (prev);
}

static int	ft_add_this_exp(t_env *prev, char *line, char *newkey, char *val)
{
	if (prev && prev->next && ft_strcmp(prev->next->key, newkey) == 0)
	{
		if (ft_strchr(line, '=') == NULL)
		{
			free(newkey);
			free(val);
			free(line);
			return (FAIL);
		}
		ft_update_exp(prev, line, val);
		free(newkey);
		return (FAIL);
	}
	return (SUCCESS);
}

int	ft_add_exp(t_env **exp_list, char *base, char *key, char *value)
{
	t_env	*new;
	char	*newkey;
	char	*newvalue;
	char	*line;

	newkey = ft_strdup(key);
	if (!newkey)
		return (SUCCESS);
	newvalue = ft_strdup(value);
	if (!newvalue)
		return (free(newkey), SUCCESS);
	line = ft_strdup(base);
	if (!line)
		return (free(newkey), free(newvalue), SUCCESS);
	new = ft_new_env(line, newkey, newvalue);
	if (!new)
		return (free(newkey), free(newvalue), free(line), SUCCESS);
	if (!*exp_list)
		return (*exp_list = new, SUCCESS);
	if (ft_add_this_exp(ft_get_right_exp(*exp_list, newkey), line, newkey,
			newvalue) == FAIL)
		return (free(new), SUCCESS);
	ft_exp_link(ft_get_right_exp(*exp_list, newkey), new, exp_list);
	return (SUCCESS);
}
