/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 15:40:46 by momrane           #+#    #+#             */
/*   Updated: 2024/04/19 16:25:06 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_last_infile(t_infile *inf_list)
{
	t_infile	*cur_inf;
	t_infile	*last_infile;

	cur_inf = inf_list;
	while (cur_inf != NULL)
	{
		if (cur_inf->filename != NULL)
			last_infile = cur_inf;
		cur_inf = cur_inf->next;
	}
	return (last_infile->filename);
}

t_outfile	*get_last_outfile(t_outfile *out_list)
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
