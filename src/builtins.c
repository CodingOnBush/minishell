/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:46:05 by momrane           #+#    #+#             */
/*   Updated: 2024/04/22 11:39:06 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_isbuiltin(t_cmd *cmd)
{
	char	*builtins[] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit", ":", "!", NULL};
	char		*str;
	int			len;
	int			i;

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
	int		fd;

	if (!data)
		return (1);
	env_list = data->env_list;
	fd = ft_get_fd_out(data, cmd);
	while (env_list)
	{
		ft_putstr_fd(env_list->key, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(env_list->value, fd);
		ft_putstr_fd("\n", fd);
		env_list = env_list->next;
	}
	if (fd != STDOUT_FILENO)
		close(fd);
	return (0);
}

static int	ft_pwd(t_data *data, t_cmd *cmd)
{
	char	*cwd;
	int		fd;

	if (!cmd || !cmd->arg_list || !cmd->arg_list->value)
		return (1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror(cmd->arg_list->value), 1);
	fd = ft_get_fd_out(data, cmd);
	ft_putstr_fd(cwd, fd);
	ft_putstr_fd("\n", fd);
	free(cwd);
	if (fd != STDOUT_FILENO)
		close(fd);
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
	int	len;

	if (!data || !cmd || !cmd->arg_list || !cmd->arg_list->value)
		return (1);
	len = ft_strlen(cmd->arg_list->value);
	if (len == 0)
		return (1);
	if (ft_strcmp(cmd->arg_list->value, "pwd") == 0)
		return (ft_pwd(data, cmd));
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
