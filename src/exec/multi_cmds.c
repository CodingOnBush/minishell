/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmds.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 13:57:26 by vvaudain          #+#    #+#             */
/*   Updated: 2024/05/02 11:18:16 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_first_cmd(t_data *data, t_cmd *cmd_to_exec)
{
	t_redir	*redir;
	int		status;

	redir = ft_get_redirs(data, cmd_to_exec);
	ft_exit_if_null(data, redir);
	dup2(redir->fd_in, STDIN_FILENO);
	if (redir->fd_out == STDOUT_FILENO)
	{
		if (dup2(data->pipe_ends[0][1], STDOUT_FILENO) == -1)
			perror(NULL);
	}
	else
		dup2(redir->fd_out, STDOUT_FILENO);
	ft_close_fd_pipes(data, redir);
	if (ft_isbuiltin(cmd_to_exec) == YES)
	{
		status = ft_exec_builtin(data, cmd_to_exec);
		ft_free_all(data);
		free(redir);
		exit(status);
	}
	free(redir);
	ft_execve(data, cmd_to_exec);
}

static void	ft_middle_cmd(t_data *data, t_cmd *cmd_to_exec, int process)
{
	t_redir	*redir;
	int		status;

	redir = ft_get_redirs(data, cmd_to_exec);
	ft_exit_if_null(data, redir);
	if (redir->fd_in == STDIN_FILENO)
		dup2(data->pipe_ends[process - 1][0], STDIN_FILENO);
	else
		dup2(redir->fd_in, STDIN_FILENO);
	if (redir->fd_out == STDOUT_FILENO)
		dup2(data->pipe_ends[process][1], STDOUT_FILENO);
	else
		dup2(redir->fd_out, STDOUT_FILENO);
	ft_close_fd_pipes(data, redir);
	if (ft_isbuiltin(cmd_to_exec) == YES)
	{
		status = ft_exec_builtin(data, cmd_to_exec);
		ft_free_all(data);
		free(redir);
		exit(status);
	}
	free(redir);
	ft_execve(data, cmd_to_exec);
}

static void	ft_last_cmd(t_data *data, t_cmd *cmd_to_exec, int process)
{
	t_redir	*redir;
	int		status;

	close(data->pipe_ends[process - 1][1]);
	redir = ft_get_redirs(data, cmd_to_exec);
	ft_exit_if_null(data, redir);
	if (redir->fd_in == STDIN_FILENO)
		dup2(data->pipe_ends[process - 1][0], STDIN_FILENO);
	else
		dup2(redir->fd_in, STDIN_FILENO);
	dup2(redir->fd_out, STDOUT_FILENO);
	ft_close_fd_pipes(data, redir);
	if (ft_isbuiltin(cmd_to_exec) == YES)
	{
		status = ft_exec_builtin(data, cmd_to_exec);
		ft_free_all(data);
		free(redir);
		exit(status);
	}
	free(redir);
	ft_execve(data, cmd_to_exec);
	printf("COUCOU\n");
}

void	ft_child_process(t_data *data, int process)
{
	t_cmd	*cmd_to_exec;

	cmd_to_exec = data->cmd_list;
	while (cmd_to_exec && process > cmd_to_exec->pos)
		cmd_to_exec = cmd_to_exec->next;
	if (cmd_to_exec == NULL || cmd_to_exec->arg_list == NULL)
		return ;
	if (process == 0)
		ft_first_cmd(data, cmd_to_exec);
	else if (process == data->cmd_nb - 1)
		ft_last_cmd(data, cmd_to_exec, process);
	else
		ft_middle_cmd(data, cmd_to_exec, process);
}
