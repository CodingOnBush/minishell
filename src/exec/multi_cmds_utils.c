/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_cmds_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/25 10:42:38 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/25 10:52:32 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_close_fd_pipes(t_data *data, t_redir *redir)
{
	if (redir->fd_in != STDIN_FILENO)
		close(redir->fd_in);
	if (redir->fd_out != STDOUT_FILENO)
		close(redir->fd_out);
	ft_close_pipes(data);
}

void	ft_exit_if_null(t_data *data, t_redir *redir)
{
	int	status;

	if (redir == NULL)
	{
		status = data->exit_status;
		ft_free_all(data);
		exit(status);
	}
	return ;
}
