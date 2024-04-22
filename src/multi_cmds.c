/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:57:26 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/21 18:54:29 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	first_cmd(t_data *data, t_cmd *cmd_to_exec)
{
	int	fd_out;
	int	fd_in;
	int status;

	fd_in = ft_get_fd_in(data, cmd_to_exec);
	fd_out = ft_get_fd_out(data, cmd_to_exec);
	dup2(fd_in, STDIN_FILENO);
	if (fd_out == STDOUT_FILENO)
	{
		if (dup2(data->pipe_ends[0][1], STDOUT_FILENO) == -1)
			perror(NULL);
	}
	else
		dup2(fd_out, STDOUT_FILENO);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	ft_close_pipes(data);
	if (ft_isbuiltin(cmd_to_exec) == YES)
	{
		status = ft_exec_builtin(data, cmd_to_exec);
		ft_free_all(data);
		exit(status);
	}
	else
		ft_execve(data, cmd_to_exec);
}

void	middle_cmd(t_data *data, t_cmd *cmd_to_exec, int process)
{
	int	fd_out;
	int	fd_in;
	int status;

	fd_in = ft_get_fd_in(data, cmd_to_exec);
	fd_out = ft_get_fd_out(data, cmd_to_exec);
	if (fd_in == STDIN_FILENO)
		dup2(data->pipe_ends[process - 1][0], STDIN_FILENO);
	else
		dup2(fd_in, STDIN_FILENO);
	if (fd_out == STDOUT_FILENO)
		dup2(data->pipe_ends[process][1], STDOUT_FILENO);
	else
		dup2(fd_out, STDOUT_FILENO);
	ft_close_pipes(data);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	if (ft_isbuiltin(cmd_to_exec) == YES)
	{
		status = ft_exec_builtin(data, cmd_to_exec);
		ft_free_all(data);
		exit(status);
	}
	else
		ft_execve(data, cmd_to_exec);
}

void	last_cmd(t_data *data, t_cmd *cmd_to_exec, int process)
{
	int	fd_out;
	int	fd_in;
	int status;

	close(data->pipe_ends[process - 1][1]);
	fd_in = ft_get_fd_in(data, cmd_to_exec);
	fd_out = ft_get_fd_out(data, cmd_to_exec);
	if (fd_in == STDIN_FILENO)
		dup2(data->pipe_ends[process - 1][0], STDIN_FILENO);
	else
		dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	ft_close_pipes(data);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	if (ft_isbuiltin(cmd_to_exec) == YES)
	{
		status = ft_exec_builtin(data, cmd_to_exec);
		ft_free_all(data);
		exit(status);
	}
	else
		ft_execve(data, cmd_to_exec);
}

void	child_process(t_data *data, int process)
{
	t_cmd	*cmd_to_exec;

	cmd_to_exec = data->cmd_list;
	while (cmd_to_exec && process > cmd_to_exec->pos)
		cmd_to_exec = cmd_to_exec->next;
	if (cmd_to_exec == NULL || cmd_to_exec->arg_list == NULL)
		return ;
	if (process == 0)
		first_cmd(data, cmd_to_exec);
	else if (process == data->cmd_nb - 1)
		last_cmd(data, cmd_to_exec, process);
	else
		middle_cmd(data, cmd_to_exec, process);
}
