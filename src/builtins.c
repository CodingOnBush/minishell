/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:46:05 by momrane           #+#    #+#             */
/*   Updated: 2024/04/21 18:54:29 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_cmd_is_builtin(t_cmd *cmd, char *cmd_name)
{
	char	*str;
	int		len;

	if (!cmd || !(cmd->arg_list) || !(cmd->arg_list->value))
		return (NO);
	str = cmd->arg_list->value;
	len = ft_strlen(str);
	if (len == 0)
		return (NO);
	if (ft_strncmp(str, cmd_name, len) == 0)
		return (YES);
	return (NO);
}

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
		if (ft_cmd_is_builtin(cmd, (char *)builtins[i]) == YES)
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

int	ft_exec_builtin(t_data *data, t_cmd *cmd)
{
	if (ft_cmd_is_builtin(cmd, "pwd"))
		return (ft_pwd(data, cmd));
	if (ft_cmd_is_builtin(cmd, "env"))
		return (ft_print_env(data, cmd));
	if (ft_cmd_is_builtin(cmd, "cd"))
		return (ft_cd(data->env_list, cmd));
	if (ft_cmd_is_builtin(cmd, "echo"))
		return (ft_echo(data, cmd));
	if (ft_cmd_is_builtin(cmd, ":"))
		return (0);
	if (ft_cmd_is_builtin(cmd, "!"))
		return (0);
	if (ft_cmd_is_builtin(cmd, "export"))
		return (ft_export(data, cmd));
	if (ft_cmd_is_builtin(cmd, "unset"))
		return (ft_unset(data, cmd->arg_list));
	if (ft_cmd_is_builtin(cmd, "exit"))
		return (ft_exit(data, cmd->arg_list));
	return (1);
}
