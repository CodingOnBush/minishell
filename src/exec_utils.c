/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:11:01 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/12 11:55:55 by momrane          ###   ########.fr       */
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

static char	*ft_create_cmd_path(char *path, char *cmd_name)
{
	char	*cmd_path;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	cmd_path = ft_strjoin(tmp, cmd_name);
	if (!cmd_path)
		return (NULL);
	free(tmp);
	return (cmd_path);
}

char	*ft_get_cmd_path(char *cmd_name)
{
	char	**path_list;
	char	*cmd_path;
	int		i;

	if (ft_strchr(cmd_name, '/') != NULL)
		return (ft_strdup(cmd_name));
	path_list = ft_split(getenv("PATH"), ':');
	if (!path_list)
		return (NULL);
	i = 0;
	while (path_list[i])
	{
		cmd_path = ft_create_cmd_path(path_list[i], cmd_name);
		if (!cmd_path)
			return (ft_free_path(path_list), NULL); //ici il ne faut pas free sinon pas de path pour dire à l'exec que la cmd n'existe pas (booleen?)
		if (access(cmd_path, F_OK) == 0)
			return (ft_free_path(path_list), cmd_path);
		free(cmd_path);
		i++;
	}
	return (ft_free_path(path_list), NULL);
}

void	cmd_not_found_error(char *cmd_name)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": command not found\n", 2);
}
