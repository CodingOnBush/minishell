/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:48:28 by momrane           #+#    #+#             */
/*   Updated: 2024/04/22 12:14:50 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

static char	*ft_extract_key(char*str)
{
	int		i;
	char	*res;

	if (ft_strchr(str, '=') == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (i == 0)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	ft_strlcpy(res, str, i + 1);
	return (res);
}

static char	*ft_extract_value(char *str)
{
	char	*res;
	int		i;
	int		j;

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
	ft_strlcpy(res, str + i, j + 1);
	return (res);
}

int	ft_export(t_data *data, t_cmd *cmd)
{
	t_arg	*args;
	char	*var_name;
	char	*var_content;

	if (!data || !cmd || !cmd->arg_list || !cmd->arg_list->value)
		return (FAIL);
	if (cmd->arg_list->next == NULL)
		return (ft_putstr_fd("minishell : unspecified behaviour\n", 2), 1);
	args = cmd->arg_list->next;
	while (args)
	{
		var_name = ft_extract_key(args->value);
		if (ft_isvalid_varname(var_name) == NO)
		{
			free(var_name);
			ft_print_export_error(args->value);
		}
		else
		{
			var_content = ft_extract_value(args->value);
			if (!var_content)
				var_content = ft_strdup("");
			if (ft_setenv(&data->env_list, var_name, var_content) == FAIL)
				return (free(var_name), free(var_content), 1);
		}
		args = args->next;
	}
	return (0);
}
