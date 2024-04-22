/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:40:46 by momrane           #+#    #+#             */
/*   Updated: 2024/04/22 17:34:36 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_outfile	*get_last_outfile(t_outfile *out_list)
{
	t_outfile	*cur;
	int			fd;

	cur = out_list;
	if (!cur)
		return (NULL);
	while (cur->next != NULL)
	{
		if (access(cur->filename, F_OK) == -1)
		{
			if (cur->append == true)
				fd = open(cur->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
			else
				fd = open(cur->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
			close(fd);
		}
		cur = cur->next;
	}
	return (cur);
}

int	ft_get_fd_out(t_data *data, t_cmd *cmd)
{
	t_outfile	*outfile;
	int			fd_out;

	fd_out = STDOUT_FILENO;
	outfile = get_last_outfile(cmd->outfile_list);
	if (!outfile)
		return (fd_out);
	if (outfile != NULL && outfile->append == YES)
		fd_out = open(outfile->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (outfile != NULL && outfile->append == NO)
		fd_out = open(outfile->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror(outfile->filename);
		ft_free_all(data);
		exit(1);
	}
	return (fd_out);
}
