/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:11:01 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/07 14:33:50 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

int	alloc_ids(t_data *data)
{
	int	i;

	i = 0;
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
char	*get_missing_file(t_infile *inf_list)
{
	t_infile	*cur_inf;

	cur_inf = inf_list;
	while (cur_inf != NULL)
	{
		if (access(cur_inf->filename, F_OK) == -1)
			return (cur_inf->filename);
		cur_inf = cur_inf->next;
	}
	return (NULL);
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

// //ft_add_slash
// static void	ft_add_slash(t_data *data, t_cmd *cmd)
// {
// 	char	*tmp;
	
// 	tmp = cmd->args[0];
// 	cmd->args[0] = ft_strjoin("/", tmp);
// 	if (!cmd->args[0])
// 	{
// 		perror("");
// 		// ft_free_exec(data);
// 		// exit(EXIT_FAILURE);
// 	}
// 	free(tmp);
// }

// //ft_join_path
// static void	ft_join_path(t_data *data, t_cmd *cmd, int count)
// {
// 	data->join_path = ft_strjoin(data->path_list[count], cmd->args[0]);
// 	if (!data->join_path)
// 	{
// 		ft_free_exec(data);
// 		exit(EXIT_FAILURE);
// 	}
// }

// char	*get_cmd_path(t_data *data, t_cmd *cmd)
// {
// 	int	count;

// 	if (!cmd->args[0])
// 		return (NULL);
// 	if (ft_strchr(cmd->args[0], '/'))
// 	{
// 		if (access(cmd->args[0], F_OK) == 0)
// 			return (ft_strdup(cmd->args[0]));
// 		else
// 			return (NULL);
// 	}
// 	if (data->path_list == NULL)
// 		return (NULL);
// 	ft_add_slash(data, cmd);
// 	count = 0;
// 	while (data->path_list[count])
// 	{
// 		ft_join_path(data, cmd, count);
// 		if (access(data->join_path, F_OK) == 0)
// 			return (data->join_path);
// 		free(data->join_path);
// 		count++;
// 	}
// 	return (NULL);
// }
