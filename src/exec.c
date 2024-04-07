/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/07 20:00:28 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_cmd_errors_found(t_cmd *cmd)
{
	char	*cmd_name;
	int		i;

	if (cmd && cmd->args && ft_strchr(cmd->args[0], '/') == NULL)
		return (NO);
	i = 0;
	cmd_name = cmd->args[0];
	while (cmd_name[i])
	{
		while (cmd_name[i] != '\0' && cmd_name[i] == '/')
			i++;
		if (cmd_name[i] == '\0')
			return (printf("minishell: %s: 1Is a directory\n", cmd_name), YES);
		i++;
		if (cmd_name[i] != '.')
			return (printf("minishell: %s: 2No such file or directory\n", cmd_name), YES);
		i++;
		if (cmd_name[i] != '.')
			return (printf("minishell: %s: 3No such file or directory\n", cmd_name), YES);
		if (cmd_name[i] == '\0')
			return (printf("minishell: %s: 4Is a directory\n", cmd_name), YES);
		if (cmd_name[i] != '/')
			return (printf("minishell: %s: 5No such file or directory\n", cmd_name), YES);
		i++;
	}
	return (NO);
}

int	ft_exec(t_data *data, t_cmd *cmd)
{
	if (ft_cmd_errors_found(cmd) == YES)
	{
		ft_free_all(data);
		exit(1);
	}
	if (cmd->cmd_path == NULL)
	{
		if (!cmd->args && !cmd->args[0])
		{
			ft_free_all(data);
			exit(EXIT_FAILURE);
		}
		// if (cmd->args[0][0] == '/' || ft_strncmp("./", cmd->args[0], 2) == 0)
		// 	perror(cmd->args[0]);
		// else
		// 	printf("minishell: %s: command not found\n", cmd->args[0]);
		ft_free_all(data);
		exit(127);
	}
	execve(cmd->cmd_path, cmd->args, data->env);
	perror(cmd->cmd_path);
	ft_free_all(data);
	exit(126);
}

int	ft_fork(t_data *data)
{
	int	process;
	
	alloc_ids(data);
	process = 0;
	while (process < data->cmd_nb)
	{
		data->ids[process] = fork();
		if (data->ids[process] == -1)
			return (perror("Forking failed"), FAIL);
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

void	ft_wait_for_children(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	if (data->cmd_nb == 1 && ft_isbuiltin(data->cmd_list))
		return ;
	while (i < data->cmd_nb)
	{
		waitpid(data->ids[i], &status, 0);
		i++;
	}
}

void	ft_launch_exec(t_data *data)
{
	if (ft_launch_heredoc(data) == FAIL || data->cmd_nb <= 0)
		return ;
	if (data->cmd_nb == 1 && ft_isbuiltin(data->cmd_list) == YES)
		ft_exec_builtin(data, data->cmd_list);
	else if (data->cmd_nb == 1 && ft_isbuiltin(data->cmd_list) == NO)
	{
		ft_fork(data);
	}
	else if (data->cmd_nb > 1 && ft_init_pipes(data) == SUCCESS)
		ft_fork(data);
	ft_wait_for_children(data);
}
