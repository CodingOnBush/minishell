/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:47:59 by momrane           #+#    #+#             */
/*   Updated: 2024/04/25 11:55:46 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_handle_dups_parent(t_data *data, t_redir *redir, t_cmd *cmd)
{
	int	fdin_save;
	int	fdout_save;

	fdin_save = dup(STDIN_FILENO);
	fdout_save = dup(STDOUT_FILENO);
	dup2(redir->fd_in, STDIN_FILENO);
	dup2(redir->fd_out, STDOUT_FILENO);
	if (redir->fd_in != STDIN_FILENO)
		close(redir->fd_in);
	if (redir->fd_out != STDOUT_FILENO)
		close(redir->fd_out);
	free(redir);
	if (ft_strcmp(cmd->arg_list->value, "exit") == 0)
	{
		dup2(fdin_save, STDIN_FILENO);
		dup2(fdout_save, STDOUT_FILENO);
		close(fdin_save);
		close(fdout_save);
	}
	data->exit_status = ft_exec_builtin(data, cmd);
	dup2(fdin_save, STDIN_FILENO);
	dup2(fdout_save, STDOUT_FILENO);
	close(fdin_save);
	close(fdout_save);
}

int	ft_exec_single_builtin(t_data *data)
{
	t_cmd	*cmd;
	t_redir	*redir;

	cmd = data->cmd_list;
	if (cmd == NULL || cmd->arg_list == NULL)
		return (data->exit_status);
	redir = ft_get_redirs(data, cmd);
	if (redir == NULL)
	{
		ft_reset_data(data);
		return (data->exit_status);
	}
	if (redir->fd_in == -1)
		return (1);
	if (redir->fd_out == -1)
	{
		if (redir->fd_in != STDIN_FILENO)
			close(redir->fd_in);
		return (1);
	}
	ft_handle_dups_parent(data, redir, cmd);
	return (data->exit_status);
}
