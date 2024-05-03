/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:32:11 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 12:32:12 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_free_pipes(int **pipe_ends, int cursor)
{
	while (cursor > 0)
	{
		close(pipe_ends[cursor][0]);
		close(pipe_ends[cursor][1]);
		if (pipe_ends[cursor])
			free(pipe_ends[cursor]);
		cursor--;
	}
	free(pipe_ends);
}

void	ft_close_pipes(t_data *data)
{
	int	count;

	count = 0;
	if (!data->pipe_ends)
		return ;
	while (count < data->cmd_nb - 1)
	{
		close(data->pipe_ends[count][0]);
		close(data->pipe_ends[count][1]);
		count++;
	}
}

int	**ft_create_pipe_ends(int pipe_nb)
{
	int	**pipe_ends;
	int	i;

	i = 0;
	pipe_ends = malloc(sizeof(int *) * pipe_nb);
	if (!pipe_ends)
		return (perror("minishell: "), NULL);
	while (i < pipe_nb)
	{
		pipe_ends[i] = malloc(sizeof(int) * 2);
		if (!pipe_ends[i] || pipe(pipe_ends[i]) == -1)
		{
			ft_free_pipes(pipe_ends, i);
			return (perror("minishell: "), NULL);
		}
		i++;
	}
	return (pipe_ends);
}
