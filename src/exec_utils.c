/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:11:01 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/04 12:30:05 by vvaudain         ###   ########.fr       */
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
	return (cmd_nb);
}

int	alloc_ids(t_data *data)
{
	int	i;

	i = 0;
	printf("cmd_nb = %d\n", data->cmd_nb);
	data->ids = malloc(sizeof(int) * data->cmd_nb);
	if (!data->ids)
	{
		perror("");
		return (FAIL);
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
void	set_cmd_pos(t_cmd *cmd_list)
{
	int		pos;
	t_cmd	*cur;

	pos = 0;
	cur = cmd_list;
	while (cur != NULL)
	{
		cur->pos = pos;
		pos++;
		cur = cur->next;
	}
}

int	is_infile(t_cmd *cmd)
{
	t_infile	*cur_inf;

	cur_inf = cmd->infile_list;
	while (cur_inf != NULL)
	{
		if (cur_inf->delimiter == NULL && cur_inf->filename != NULL)
			return (YES);
		cur_inf = cur_inf->next;
	}
	return (0);
}
char	*all_files_exist(t_infile *inf_list)
{
	t_infile	*cur_inf;

	cur_inf = inf_list;
	while (cur_inf != NULL)
	{
		if (access(cur_inf->filename, F_OK) == -1)
			return (cur_inf->filename);
		cur_inf = cur_inf->next;
	}
	return (YES);
}

char	*get_last_infile(t_infile *inf_list)
{
	t_infile	*cur_inf;
	t_infile	*last_infile;

	cur_inf = inf_list;
	while (cur_inf != NULL)
	{
		if (cur_inf->delimiter == NULL && cur_inf->filename != NULL)
			last_infile = cur_inf;
		cur_inf = cur_inf->next;
	}
	return (last_infile->filename);
}