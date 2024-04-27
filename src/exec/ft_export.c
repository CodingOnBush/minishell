/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:48:28 by momrane           #+#    #+#             */
/*   Updated: 2024/04/27 13:00:13 by momrane          ###   ########.fr       */
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

static char	*ft_get_var_name(char *str)
{
	char	*var_name;
	char	*equal;

	equal = ft_strchr(str, '=');
	var_name = ft_substr(str, 0, equal - str);
	if (!var_name)
		return (NULL);
	if (ft_isvalid_varname(var_name) == NO)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		free(var_name);
		return (NULL);
	}
	return (var_name);
}

static char	*ft_get_var_content(char *str)
{
	char	*var_content;
	char	*equal;

	equal = ft_strchr(str, '=');
	if (!equal)
		return (NULL);
	var_content = ft_strdup(equal + 1);
	if (!var_content)
		return (ft_strdup(""));
	return (var_content);
}

static int	ft_handle_line(t_data *data, char *line)
{
	char	*var_name;
	char	*var_content;

	if (ft_strchr(line, '=') != NULL)
	{
		var_name = ft_get_var_name(line);
		if (!var_name)
			return (1);
		var_content = ft_get_var_content(line);
		if (var_content != NULL)
		{
			if (ft_setenv(&data->env_list, var_name, var_content) == FAIL)
				return (free(var_name), free(var_content), 1);
		}
	}
	else if (ft_isvalid_varname(line) == NO)
	{
		ft_putstr_fd("minishell: export: `", 2);
		ft_putstr_fd(line, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (1);
	}
	return (0);
}

int	ft_export(t_data *data, t_cmd *cmd)
{
	t_arg	*args;
	int		exit_status;

	exit_status = 0;
	if (!data || !cmd || !cmd->arg_list || !cmd->arg_list->value)
		return (FAIL);
	if (cmd->arg_list->next == NULL)
		return (ft_print_exports_var(data), 0);
	args = cmd->arg_list->next;
	while (args)
	{
		exit_status = ft_handle_line(data, args->value);
		args = args->next;
	}
	return (exit_status);
}
