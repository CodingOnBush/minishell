/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 16:14:12 by momrane           #+#    #+#             */
/*   Updated: 2024/04/25 19:06:06 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_isdirectory(char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
			return (YES);
		else
			return (NO);
	}
	return (NO);
}

static void	ft_check_errors(t_data *data, t_cmd *cmd)
{
	if (ft_isdirectory(cmd->cmd_path) == YES)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->arg_list->value, 2);
		ft_putstr_fd(": Is a directory\n", 2);
		ft_free_all(data);
		exit(126);
	}
	if (!cmd->cmd_path || (cmd->cmd_path && cmd->cmd_path[0] == '\0'))
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->arg_list->value, 2);
		ft_putstr_fd(": command not found\n", 2);
		ft_free_all(data);
		exit(127);
	}
	if (access(cmd->cmd_path, F_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->arg_list->value, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		ft_free_all(data);
		exit(127);
	}
}

int	ft_execve(t_data *data, t_cmd *cmd)
{
	char	**env;

	if (!cmd->arg_list || !cmd->arg_list->value)
		return (SUCCESS);
	cmd->cmd_path = ft_get_cmd_path(data, cmd->arg_list->value);
	ft_check_errors(data, cmd);
	if (access(cmd->cmd_path, X_OK) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->arg_list->value, 2);
		ft_putstr_fd(": Permission denied\n", 2);
		ft_free_all(data);
		exit(126);
	}
	env = ft_create_env(data);
	execve(cmd->cmd_path, cmd->args, env);
	ft_free_env(env);
	ft_putstr_fd("minishell: ", 2);
	perror(cmd->cmd_path);
	ft_free_all(data);
	exit(126);
}

static int	ft_fork(t_data *data)
{
	int	process;

	data->ids = malloc(sizeof(int) * data->cmd_nb);
	if (!data->ids)
		return (1);
	process = 0;
	while (process < data->cmd_nb)
	{
		data->ids[process] = fork();
		if (data->ids[process] == -1)
			return (perror("minishell :"), FAIL);
		if (data->ids[process] == 0)
		{
			if (data->cmd_nb == 1)
				ft_exec_single_cmd(data);
			else
				ft_child_process(data, process);
			ft_free_all(data);
			exit(0);
		}
		process++;
	}
	ft_close_pipes(data);
	return (SUCCESS);
}

void	ft_launch_exec(t_data *data)
{
	if (data->cmd_nb <= 0)
		return ;
	if (ft_launch_heredoc(data) == FAIL)
		return ;
	if (data->cmd_nb == 1 && ft_isbuiltin(data->cmd_list) == YES)
	{
		data->exit_status = ft_exec_single_builtin(data);
	}
	else if (data->cmd_nb == 1 && ft_isbuiltin(data->cmd_list) == NO)
	{
		ft_fork(data);
	}
	else if (data->cmd_nb > 1)
	{
		data->pipe_ends = ft_create_pipe_ends(data->cmd_nb - 1);
		if (!data->pipe_ends)
			return ;
		ft_fork(data);
	}
}
