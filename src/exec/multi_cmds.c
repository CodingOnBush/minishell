/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:57:26 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/07 02:13:46 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	first_cmd(t_data *data, t_cmd *cmd_to_exec)
{
	int	fd_out;
	int	fd_in;

	fd_in = ft_get_fd_in(data, cmd_to_exec);
	fd_out = ft_get_fd_out(data, cmd_to_exec);
	dup2(fd_in, STDIN_FILENO);
	if (fd_out == STDOUT_FILENO)
		dup2(data->pipe_ends[0][1], STDOUT_FILENO);
	else
		dup2(fd_out, STDOUT_FILENO);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	ft_close_pipes(data);
	if (ft_isbuiltin(cmd_to_exec) == YES)
		ft_exec_builtin(data, cmd_to_exec);
	else
		ft_exec(data, cmd_to_exec);
}

void	middle_cmd(t_data *data, t_cmd *cmd_to_exec, int process)
{
	int	fd_out;
	int	fd_in;

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
		ft_exec_builtin(data, cmd_to_exec);
	else
		ft_exec(data, cmd_to_exec);
}

void	last_cmd(t_data *data, t_cmd *cmd_to_exec, int process)
{
	int	fd_out;
	int	fd_in;

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
		ft_exec_builtin(data, cmd_to_exec);
	else
		ft_exec(data, cmd_to_exec);
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

int	ft_init_pipes(t_data *data)
{
	int	count;

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
