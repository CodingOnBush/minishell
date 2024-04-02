/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:38:01 by momrane           #+#    #+#             */
/*   Updated: 2024/04/02 17:04:17 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	do_pipes(t_data *data)
{
	int		count;
	
	count = 0;
	alloc_pipes(data);
	while (count < data->cmd_nb - 1)
	{
		if (pipe(data->pipes[count]) == -1)
		{
			perror(NULL);
			return (FAIL);
		}
		count++;
	}
	return (SUCCESS);
}

int	ft_start_exec(t_data *data)
{
	int	cmd_nb;
	
	(void)data;
	cmd_nb = get_cmd_nb(data->cmd_list);
	alloc_ids(data);
	if (do_pipes(data) == FAIL)
		return (FAIL);
	else
		ft_fork(data);
}
