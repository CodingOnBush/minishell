/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:48:28 by momrane           #+#    #+#             */
/*   Updated: 2024/04/22 19:48:44 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_isvalid_varname(char *varname)
{
	int		i;

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

static void	ft_print_export_error(char *arg_error)
{
	ft_putstr_fd("minishell: export: `", 2);
	ft_putstr_fd(arg_error, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
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
		ft_print_export_error(str);
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

int	ft_export(t_data *data, t_cmd *cmd)
{
	t_arg	*args;
	char	*var_name;
	char	*var_content;
	int		exit_status;

	exit_status = 0;
	if (!data || !cmd || !cmd->arg_list || !cmd->arg_list->value)
		return (FAIL);
	if (cmd->arg_list->next == NULL)
		return (ft_putstr_fd("minishell : unspecified behaviour\n", 2), 1);
	args = cmd->arg_list->next;
	while (args)
	{
		if (ft_strchr(args->value, '=') != NULL)
		{
			var_name = ft_get_var_name(args->value);
			if (var_name)
			{
				var_content = ft_get_var_content(args->value);
				if (var_content)
				{
					if (ft_setenv(&data->env_list, var_name, var_content) == FAIL)
						return (free(var_name), free(var_content), 1);
				}
			}
			else
				exit_status = 1;
		}
		else if (ft_isvalid_varname(args->value) == NO)
		{
			ft_print_export_error(args->value);
			exit_status = 1;
		}
		args = args->next;
	}
	return (exit_status);
}
