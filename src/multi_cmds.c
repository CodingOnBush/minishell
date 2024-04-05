/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:57:26 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/05 16:07:10 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	first_cmd(t_data *data, t_cmd *cmd_to_exec)
{
	int		fd_out;
	int		fd_in;

	// printf("I am in the first command function\n");
	fd_in = ft_get_fd_in(data, cmd_to_exec);
	fd_out = ft_get_fd_out(data, cmd_to_exec);
	close(data->pipe_ends[0][0]);
	dup2(fd_in, STDIN_FILENO);
	if (fd_out == STDOUT_FILENO)
	{
		// printf("pipe_ends[0][0]: %d\n", data->pipe_ends[0][0]);
		// printf("pipe_ends[0][1]: %d\n", data->pipe_ends[0][1]);
		dup2(data->pipe_ends[0][1], STDOUT_FILENO);
	}
	else
		dup2(fd_out, STDOUT_FILENO);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	if (ft_isbuiltin(cmd_to_exec->arg_list->value) == YES)
		ft_exec_builtin(data, cmd_to_exec);
	else
		ft_exec(data, cmd_to_exec);
}

void	middle_cmd(t_data *data, t_cmd *cmd_to_exec, int process)
{
	int		fd_out;
	int		fd_in;

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
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	if (ft_isbuiltin(cmd_to_exec->arg_list->value) == YES)
		ft_exec_builtin(data, cmd_to_exec);
	else
		ft_exec(data, cmd_to_exec);
}

void	last_cmd(t_data *data, t_cmd *cmd_to_exec, int process)
{
	int		fd_out;
	int		fd_in;

	// printf("I am in the last command function\n");
	close(data->pipe_ends[process - 1][1]);
	fd_in = ft_get_fd_in(data, cmd_to_exec);
	fd_out = ft_get_fd_out(data, cmd_to_exec);
	if (fd_in == STDIN_FILENO)
	{
		// printf("pipe_ends[process - 1][0]: %d\n", data->pipe_ends[process - 1][0]);
		dup2(data->pipe_ends[process - 1][0], STDIN_FILENO);
	}
	else
		dup2(fd_in, STDIN_FILENO);
	// printf("fd_out: %d\n", fd_out);
	dup2(fd_out, STDOUT_FILENO);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	if (ft_isbuiltin(cmd_to_exec->arg_list->value) == YES)
		ft_exec_builtin(data, cmd_to_exec);
	else
		ft_exec(data, cmd_to_exec);
}

void	child_process(t_data *data, int process)
{
	t_cmd	*cmd_to_exec;

	cmd_to_exec = data->cmd_list;
	// printf("process: %d\n", process);
	while (cmd_to_exec && process > cmd_to_exec->pos)
		cmd_to_exec = cmd_to_exec->next;
	if (cmd_to_exec == NULL || cmd_to_exec->arg_list == NULL)
		return ;
	// printf("cmd pos: %d\n", cmd_to_exec->pos);
	if (process == 0)
		first_cmd(data, cmd_to_exec);
	else if (process == data->cmd_nb - 1)
		last_cmd(data, cmd_to_exec, process);
	else
		middle_cmd(data, cmd_to_exec, process);
}

int	do_pipes(t_data *data)
{
	int		count;
	
	count = 0;
	alloc_pipes(data);
	while (count < data->cmd_nb - 1)
	{
		if (pipe(data->pipe_ends[count]) == -1)
		{
			perror(NULL);
			ft_free_exec(data);
			return (FAIL);
		}
		count++;
	}
	return (SUCCESS);
}