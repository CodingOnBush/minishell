/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/03 15:18:31 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

int	ft_fork(t_data *data)
{
	int	process;
	
	process = -1;
	while (++process < data->cmd_nb)
	{
		data->ids[process][0] = fork();
		if (data->ids[process][0] == -1)
			return (perror("Forking failed"), FAIL);
		else if (data->ids[process][0] == 0)
			printf("child process\n");
		// child_process(data, process);
		process++;
		if (process < data->cmd_nb)
		{
			data->ids[process][0] = fork();
			if (data->ids[process][0] < 0)
				return (perror("Forking failed"), FAIL);
			else if (data->ids[process][0] == 0)
				printf("child process\n");
			// child_process(data, process);
		}
	}
	ft_close_pipes(data);
	return (SUCCESS);
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
	return (SUCCESS);
}
