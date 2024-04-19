/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/19 18:12:13 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

static void	ft_free_pipes(int **pipe_ends, int cursor)
{
	while (cursor > 0)
	{
		close(pipe_ends[cursor][0]);
		close(pipe_ends[cursor][1]);
		if (pipe_ends[cursor])
			free(pipe_ends[cursor]);
		cursor--;
	}
	free(pipe_ends);
}

static int	**ft_create_pipe_ends(int pipe_nb)
{
	int	**pipe_ends;
	int	i;

	i = 0;
	pipe_ends = malloc(sizeof(int *) * pipe_nb);
	if (!pipe_ends)
		return (perror("minishell: "), NULL);
	while (i < pipe_nb)
	{
		pipe_ends[i] = malloc(sizeof(int) * 2);
		if (!pipe_ends[i] || pipe(pipe_ends[i]) == -1)
		{
			ft_free_pipes(pipe_ends, i);
			return (perror("minishell: "), NULL);
		}
		i++;
	}
	return (pipe_ends);
}

void	ft_launch_exec(t_data *data)
{
	if (ft_launch_heredoc(data) == FAIL || data->cmd_nb <= 0)
		return;
	if (data->cmd_nb >= 1 && ft_isbuiltin(data->cmd_list) == NO)
	{
		data->pipe_ends = ft_create_pipe_ends(data->cmd_nb - 1);
		if (!data->pipe_ends)
			return ;
		ft_fork(data);
	}
	else if (data->cmd_nb == 1 && ft_isbuiltin(data->cmd_list) == YES)
		ft_exec_single_cmd(data);
}
