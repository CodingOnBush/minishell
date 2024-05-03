/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:18:48 by vvaudain          #+#    #+#             */
/*   Updated: 2024/05/02 12:21:56 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_free_heredocs(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->hdnum)
	{
		if (data->hd_files && data->hd_files[i])
		{
			free(data->hd_files[i]);
			data->hd_files[i] = NULL;
		}
		i++;
	}
	if (data->hd_files)
		free(data->hd_files);
	if (data->fd_hd)
		free(data->fd_hd);
	data->hd_files = NULL;
	data->fd_hd = NULL;
}

static void	ft_free_pipe_ends(t_data *data)
{
	int	i;

	i = 0;
	if (data->pipe_ends)
	{
		ft_close_pipes(data);
		while (i < data->cmd_nb - 1)
		{
			if (data->pipe_ends[i])
				free(data->pipe_ends[i]);
			i++;
		}
		free(data->pipe_ends);
		data->pipe_ends = NULL;
	}
}

static void	ft_unlink(t_data *data)
{
	int	i;

	i = 0;
	if (!data || !data->hd_files)
		return ;
	while (i < data->hdnum && data->hd_files[i] != NULL)
	{
		if (data->hd_files[i])
			unlink(data->hd_files[i]);
		i++;
	}
}

void	ft_reset_data(t_data *data)
{
	if (!data)
		return ;
	ft_unlink(data);
	ft_free_heredocs(data);
	if (data->token_list != NULL)
		ft_free_tokens(&data->token_list);
	if (data->cmd_list != NULL)
		ft_free_cmd_list(&data->cmd_list);
	if (data->fd_hd != NULL)
		free(data->fd_hd);
	if (data->line != NULL)
		free(data->line);
	if (data->pipe_ends)
		ft_free_pipe_ends(data);
	if (data->ids != NULL)
		free(data->ids);
	data->hdnum = 0;
	data->cmd_nb = 0;
	data->step = 0;
	data->line = NULL;
	data->fd_hd = NULL;
	data->ids = NULL;
}

void	ft_free_all(t_data *data)
{
	if (!data)
		return ;
	ft_reset_data(data);
	if (data->env_list)
		ft_free_env_list(&data->env_list);
	if (data->exp_list)
		ft_free_env_list(&data->exp_list);
	free(data);
}
