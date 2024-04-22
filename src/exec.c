/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/21 18:54:29 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	cmd_not_found_error(char *cmd_name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": command not found\n", 2);
}

int ft_execve(t_data *data, t_cmd *cmd)
{
	char	**new_env;

	if (!cmd->arg_list || !cmd->arg_list->value)
		return (SUCCESS);
	// if (access(cmd->arg_list->value, X_OK) == 0) //ici est-ce que c'est pas 1 plutot?
	// {
	// 	ft_putstr_fd("minishell: ", 2);
	// 	ft_putstr_fd(cmd->arg_list->value, 2);
	// 	ft_putstr_fd(": Is a directory\n", 2);
	// 	// printf("minishell: %s: Is a directory\n", cmd->arg_list->value);
	// 	ft_free_all(data);
	// 	exit(126);
	// }
	cmd->cmd_path = ft_get_cmd_path(data, cmd->arg_list->value);
	if (!cmd->cmd_path || (cmd->cmd_path && cmd->cmd_path[0] == '\0'))
	{
		cmd_not_found_error(cmd->arg_list->value);
		ft_free_all(data);
		exit(127);
	}
	new_env = data->env;
	execve(cmd->cmd_path, cmd->args, new_env);
	// ft_free_env(new_env); // line to uncomment
	ft_putstr_fd("minishell: ", 2);
	perror(cmd->cmd_path);
	ft_free_all(data);
	exit(126);
}

static int	ft_fork(t_data *data)
{
	int process;

	alloc_ids(data);
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
				child_process(data, process);
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
		return;
	if (ft_launch_heredoc(data) == FAIL)
		return;	
	if (data->cmd_nb == 1 && ft_isbuiltin(data->cmd_list) == YES)
	{
		ft_exec_single_cmd(data);
	}
	else if (data->cmd_nb >= 1 && ft_isbuiltin(data->cmd_list) == NO)
	{
		data->pipe_ends = ft_create_pipe_ends(data->cmd_nb - 1);
		if (!data->pipe_ends)
			return ;
		ft_fork(data);
	}
}
