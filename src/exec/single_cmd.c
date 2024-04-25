/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:46:13 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/25 10:26:15 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_exec_single_cmd(t_data *data)
{
	t_cmd	*cmd;
	t_redir	*redir;
	int		exit_status;

	cmd = data->cmd_list;
	if (cmd == NULL || cmd->arg_list == NULL)
		return ;
	redir = ft_get_redirs(data, cmd);
	if (redir == NULL)
	{
		exit_status = data->exit_status;
		ft_free_all(data);
		exit(exit_status);
	}
	dup2(redir->fd_in, STDIN_FILENO);
	dup2(redir->fd_out, STDOUT_FILENO);
	if (redir->fd_in != STDIN_FILENO)
		close(redir->fd_in);
	if (redir->fd_out != STDOUT_FILENO)
		close(redir->fd_out);
	free(redir);
	ft_execve(data, cmd);
}
