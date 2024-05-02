/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:48:28 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 09:39:53 by momrane          ###   ########.fr       */
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

static int	ft_add_this_exp(t_env *prev, char *line, char *newkey,
		char *newvalue)
{
	// t_env	*cur;

	// t_env	*prev;
	// cur = *exp_list;
	// if (!cur)
	// 	return (*exp_list = new, SUCCESS);
	// prev = ft_get_right_exp(*exp_list, newkey);
	if (prev && prev->next && ft_strcmp(prev->next->key, newkey) == 0)
	{
		if (ft_strchr(line, '=') == NULL)
		{
			free(newkey);
			free(newvalue);
			free(line);
			return (FAIL);
		}
		ft_update_exp(prev, line, newvalue);
		free(newkey);
		return (FAIL);
	}
	//
	return (SUCCESS);
}

static void	ft_add_exp(t_env **exp_list, char *base, char *key, char *value)
{
	t_env	*new;
	char	*newkey;
	char	*newvalue;
	char	*line;

	newkey = ft_strdup(key);
	if (!newkey)
		return ;
	newvalue = ft_strdup(value);
	if (!newvalue)
		return (free(newkey));
	line = ft_strdup(base);
	if (!line)
		return (free(newkey), free(newvalue));
	new = ft_new_env(line, newkey, newvalue);
	if (!new)
		return (free(newkey), free(newvalue), free(line));
	if (!*exp_list)
	{
		*exp_list = new;
		return ;
	}
	// prev = ft_get_right_exp(*exp_list, newkey);
	if (ft_add_this_exp(ft_get_right_exp(*exp_list, newkey), line, newkey, newvalue) == FAIL)
		free(new);
	ft_exp_link(ft_get_right_exp(*exp_list, newkey), new, exp_list);
}

void	ft_remove_exp(t_env **exp_list, char *key)
{
	t_env	*cur;
	t_env	*prev;

	if (!*exp_list)
		return ;
	cur = *exp_list;
	prev = NULL;
	while (cur && ft_strcmp(cur->key, key) != 0)
	{
		prev = cur;
		cur = cur->next;
	}
	if (!cur)
		return ;
	if (prev == NULL)
		*exp_list = cur->next;
	else
		prev->next = cur->next;
	free(cur->key);
	free(cur->value);
	free(cur->base);
	free(cur);
}

static int	ft_handle_line(t_data *data, char *line)
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

static void	ft_print(char *msg, int fd)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(msg, fd);
	ft_putstr_fd("\n", fd);
}

static int	ft_is_an_option(char *str)
{
	if (!str || str[0] != '-')
		return (NO);
	if (ft_strcmp(str, "--") == 0 || ft_strcmp(str, "-") == 0)
		return (NO);
	if (ft_strncmp(str, "--", 2) == 0 && str[2] != '\0')
		return (YES);
	if (ft_strncmp(str, "-", 1) == 0 && str[1] != '\0')
		return (YES);
	return (NO);
}

int	ft_export(t_data *data, t_cmd *cmd)
{
	t_arg	*args;
	int		exit_status;

	exit_status = 0;
	if (!data || !cmd || !cmd->arg_list || !cmd->arg_list->value)
		return (FAIL);
	args = cmd->arg_list;
	if (args->next == NULL)
		return (ft_print_exports_var(data), 0);
	args = args->next;
	if (ft_strcmp(args->value, "--") == 0 && args->next == NULL)
		return (ft_print_exports_var(data), 0);
	if (ft_strcmp(args->value, "--") == 0 && args->next != NULL)
		args = args->next;
	if (ft_is_an_option(args->value) == YES)
		return (ft_print("export: options are not allowed", 2), 2);
	while (args)
	{
		if (ft_handle_line(data, args->value) == FAIL)
			exit_status = 1;
		args = args->next;
	}
	return (exit_status);
}
