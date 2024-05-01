/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:11:17 by momrane           #+#    #+#             */
/*   Updated: 2024/05/01 20:38:11 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isbuiltin(t_cmd *cmd)
{
	char	*str;

	if (!cmd || !cmd->arg_list || !cmd->arg_list->value)
		return (NO);
	str = cmd->arg_list->value;
	if (ft_strcmp(str, "echo") == 0 || ft_strcmp(str, "cd") == 0
		|| ft_strcmp(str, "pwd") == 0 || ft_strcmp(str, "export") == 0
		|| ft_strcmp(str, "unset") == 0 || ft_strcmp(str, "env") == 0
		|| ft_strcmp(str, "exit") == 0 || ft_strcmp(str, ":") == 0
		|| ft_strcmp(str, "!") == 0)
		return (YES);
	return (NO);
}

static int	ft_is_option(char *str)
{
	if (!str || ft_strcmp(str, "--") == 0 || ft_strcmp(str, "-") == 0)
		return (NO);
	if (*str == '-' && *(str + 1) != '\0')
		return (YES);
	return (NO);
}

static int	ft_pwd(t_cmd *cmd)
{
	char	*cwd;
	t_arg	*arg;

	if (!cmd || !cmd->arg_list || !cmd->arg_list->value)
		return (1);
	arg = cmd->arg_list;
	if (arg->next && ft_is_option(arg->next->value))
		return (ft_putstr_fd("minishell: pwd: options are not allowed\n", 2),
			2);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ft_putstr_fd("minishell: ", 2), perror(arg->value), 1);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	free(cwd);
	return (0);
}

static int	ft_unset(t_data *data, t_arg *arg_list)
{
	t_arg	*cur;

	if (!data || !arg_list || !arg_list->value)
		return (FAIL);
	if (arg_list->next == NULL)
		return (0);
	cur = arg_list->next;
	if (cur && ft_is_option(cur->value) == YES)
	{
		ft_putstr_fd("minishell: unset: `", 2);
		ft_putstr_fd(cur->value, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (2);
	}
	while (cur != NULL)
	{
		ft_remove_env(&data->env_list, cur->value);
		ft_remove_exp(&data->exp_list, cur->value);
		cur = cur->next;
	}
	return (0);
}

int	ft_exec_builtin(t_data *data, t_cmd *cmd)
{
	if (!data || !cmd || !cmd->arg_list || !cmd->arg_list->value)
		return (1);
	if (ft_strlen(cmd->arg_list->value) == 0)
		return (1);
	if (ft_strcmp(cmd->arg_list->value, "pwd") == 0)
		return (ft_pwd(cmd));
	if (ft_strcmp(cmd->arg_list->value, "env") == 0)
		return (ft_print_env(data));
	if (ft_strcmp(cmd->arg_list->value, "cd") == 0)
		return (ft_cd(data->env_list, cmd));
	if (ft_strcmp(cmd->arg_list->value, "echo") == 0)
		return (ft_echo(data, cmd));
	if (ft_strcmp(cmd->arg_list->value, ":") == 0)
		return (0);
	if (ft_strcmp(cmd->arg_list->value, "!") == 0)
		return (1);
	if (ft_strcmp(cmd->arg_list->value, "export") == 0)
		return (ft_export(data, cmd));
	if (ft_strcmp(cmd->arg_list->value, "unset") == 0)
		return (ft_unset(data, cmd->arg_list));
	if (ft_strcmp(cmd->arg_list->value, "exit") == 0)
		return (ft_exit(data, cmd->arg_list));
	return (1);
}
