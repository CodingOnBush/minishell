/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 09:50:04 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 10:52:05 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_isvalid_varname(char *varname)
{
	int	i;

	i = 0;
	if (!varname || !varname[0] || ft_isdigit(varname[0]))
		return (NO);
	while (varname[i])
	{
		if (!ft_isalnum(varname[i]) && varname[i] != '_')
			return (NO);
		i++;
	}
	return (YES);
}

static void	ft_not_a_valid_identifier(char *str)
{
	ft_putstr_fd("minishell: export: `", 2);
	if (str)
		ft_putstr_fd(str, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
}

static int	ft_add_it(t_env **env_list, t_env *new, char *newkey,
		char *newvalue)
{
	t_env	*cur;
	t_env	*prev;

	cur = *env_list;
	if (!cur)
		return (*env_list = new, SUCCESS);
	prev = cur;
	while (cur)
	{
		if (ft_strcmp(cur->key, newkey) == 0)
		{
			if (cur->value)
				free(cur->value);
			cur->value = newvalue;
			if (newkey)
				free(newkey);
			return (free(new), SUCCESS);
		}
		prev = cur;
		cur = cur->next;
	}
	prev->next = new;
	return (SUCCESS);
}

static void	ft_add_env(t_env **env_list, char *key, char *value)
{
	t_env	*new;
	char	*newkey;
	char	*newvalue;

	newkey = ft_strdup(key);
	if (!newkey)
		return ;
	newvalue = ft_strdup(value);
	if (!newvalue)
		return (free(newkey));
	new = ft_new_env(NULL, newkey, newvalue);
	if (!new)
		return (free(newkey), free(newvalue));
	ft_add_it(env_list, new, newkey, newvalue);
}

int	ft_handle_line(t_data *data, char *line)
{
	char	*key;
	char	*value;

	key = ft_substr(line, 0, ft_strchr(line, '=') - line);
	if (ft_isvalid_varname(key) == NO)
		return (free(key), ft_not_a_valid_identifier(line), FAIL);
	value = ft_substr(line, ft_strchr(line, '=') - line + 1, ft_strlen(line));
	if (ft_strchr(line, '=') != NULL)
		ft_add_env(&data->env_list, key, value);
	if (key && key[0] == '_' && key[1] == '\0')
		return (free(key), free(value), SUCCESS);
	ft_add_exp(&data->exp_list, line, key, value);
	free(key);
	free(value);
	return (SUCCESS);
}
