/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:11:01 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/03 15:28:07 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "../inc/minishell.h"

void	ft_close_pipes(t_data *data)
{
	int	count;

	count = 0;
	while (count < data->cmd_nb - 1)
	{
		close(data->pipe_ends[count][0]);
		close(data->pipe_ends[count][1]);
		count ++;
	}
}

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
	printf("cmd_nb ici = %d\n", cmd_nb);
	return (cmd_nb);
}

int	alloc_ids(t_data *data)
{
	int	i;

	i = 0;
	printf("cmd_nb = %d\n", data->cmd_nb);
	data->ids = malloc(sizeof(int*) * data->cmd_nb);
	if (!data->ids)
	{
		perror("");
		return (FAIL);
	}
	while (i < data->cmd_nb)
	{
		data->ids[i] = &i;
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
	return (SUCCESS);
}
