/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:46:05 by momrane           #+#    #+#             */
/*   Updated: 2024/04/20 01:53:41 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	ft_cmdcmp(t_cmd *cmd, char *cmd_name)
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
		if (ft_cmdcmp(cmd, (char *)builtins[i]) == YES)
			return (YES);
		i++;
	}
	return (NO);
}


int	ft_exec_builtin(t_data *data, t_cmd *cmd)
{
	if (ft_cmdcmp(cmd, "pwd") == YES)
		return (ft_pwd(data, cmd));
	if (ft_cmdcmp(cmd, "cd") == YES)
		return (ft_cd(data->env_list, cmd));
	if (ft_cmdcmp(cmd, "echo") == YES)
		return (ft_echo(data, cmd));
	if (ft_cmdcmp(cmd, "env") == YES)
		return (ft_print_env(data, cmd));
	if (ft_cmdcmp(cmd, ":") == YES || ft_cmdcmp(cmd, "!") == YES)
		return (0);
	if (ft_cmdcmp(cmd, "export") == YES)
		return (ft_export(data, cmd));
	if (ft_cmdcmp(cmd, "unset") == YES)
		return (ft_unset(data, cmd->arg_list));
	if (ft_cmdcmp(cmd, "exit") == YES)
		return (ft_exit(data, cmd->arg_list));
	return (1);
}
