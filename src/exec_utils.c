/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:11:01 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/02 17:00:20 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

int	get_cmd_nb(t_cmd *cmd_list)
{
	int		cmd_nb;
	t_cmd	*cur;

	cmd_nb = 0;
	cur = cmd_list;
	while (cur != NULL)
	{
		cmd_nb++;
		cur = cur->next;
	}
	return (cmd_nb);
}

int	alloc_ids(t_data *data)
{
	int	i;

	i = 0;
	data->ids = malloc(sizeof(int*) * data->cmd_nb);
	if (!data->ids)
	{
		perror("");
		return (FAIL);
	}
	while (i < data->cmd_nb)
	{
		data->ids[i] = i;
		i++;
	}
	return (SUCCESS);
}

int	alloc_pipes(t_data *data)
{
	int	i;

	i = 0;
	data->pipe_ends = malloc(sizeof(int*) * data->cmd_nb - 1);
	if (!data->pipe_ends)
	{
		perror("");
		return (FAIL);
	}
	while (i < data->cmd_nb - 1)
	{
		data->pipe_ends[i] = malloc(sizeof(int) * 2);
		if (!data->pipe_ends[i])
		{
			perror("");
			return (FAIL);
		}
		i++;
	}
}
