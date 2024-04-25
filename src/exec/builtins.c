/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:11:17 by momrane           #+#    #+#             */
/*   Updated: 2024/04/25 15:22:44 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_isbuiltin(t_cmd *cmd)
{
	char		*str;
	int			len;
	int			i;
	char *const	builtins[] = {"echo", "cd", "pwd", "export", "unset", "env",
		"exit", ":", "!", NULL};

	if (!cmd || !(cmd->arg_list) || !(cmd->arg_list->value))
		return (NO);
	str = cmd->arg_list->value;
	len = ft_strlen(str);
	if (len == 0)
		return (NO);
	i = 0;
	while (builtins[i])
	{
		if (ft_strncmp(cmd->arg_list->value, builtins[i], len) == 0)
			return (YES);
		i++;
	}
	return (NO);
}

static int	ft_print_env(t_data *data, t_cmd *cmd)
{
	t_env	*env_list;

	if (!data)
		return (1);
	(void)cmd;
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

static int	ft_pwd(t_cmd *cmd)
{
	char	*cwd;

	if (!cmd || !cmd->arg_list || !cmd->arg_list->value)
		return (1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror(cmd->arg_list->value), 1);
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
	while (cur != NULL)
	{
		ft_remove_env(&data->env_list, cur->value);
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
		return (ft_print_env(data, cmd));
	if (ft_strcmp(cmd->arg_list->value, "cd") == 0)
		return (ft_cd(data->env_list, cmd));
	if (ft_strcmp(cmd->arg_list->value, "echo") == 0)
		return (ft_echo(data, cmd));
	if (ft_strcmp(cmd->arg_list->value, ":") == 0)
		return (0);
	if (ft_strcmp(cmd->arg_list->value, "!") == 0)
		return (0);
	if (ft_strcmp(cmd->arg_list->value, "export") == 0)
		return (ft_export(data, cmd));
	if (ft_strcmp(cmd->arg_list->value, "unset") == 0)
		return (ft_unset(data, cmd->arg_list));
	if (ft_strcmp(cmd->arg_list->value, "exit") == 0)
		return (ft_exit(data, cmd->arg_list));
	return (1);
}
