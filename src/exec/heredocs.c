/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:48:50 by vvaudain          #+#    #+#             */
/*   Updated: 2024/05/02 12:25:47 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	writing_loop(t_data *data, int fd_hd, char *delimiter,
		bool to_expand)
{
	char	*line;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("warning: here-document delimited by end of file\n",
				2);
			break ;
		}
		if (to_expand == true && ft_strchr(line, '$') != NULL && ft_strcmp(line,
				delimiter) != 0)
			line = ft_get_expanded_str(data, line);
		if (ft_strcmp(line, delimiter) == 0)
			break ;
		else
		{
			line = ft_super_strjoin(line, ft_strdup("\n"));
			write(fd_hd, line, ft_strlen(line));
			free(line);
		}
	}
	free(line);
}

static int	ft_execute_hd(t_data *data, t_cmd *cmd, int *fd_hd, int i)
{
	t_infile	*cur_inf;
	int			count;

	cur_inf = cmd->infile_list;
	count = 0;
	while (cur_inf != NULL && (i + count) < data->hdnum)
	{
		if (cur_inf->delimiter != NULL)
		{
			fd_hd[i + count] = open(data->hd_files[i + count],
					O_WRONLY | O_RDONLY | O_CREAT, 0644);
			if (fd_hd[i + count] == -1 || fd_hd[i + count] > FDMAX)
				return (ft_print_err(HDEXEC), ft_free_all(data), FAIL);
			writing_loop(data, fd_hd[i + count], cur_inf->delimiter,
				cur_inf->to_expand);
			close(fd_hd[i + count]);
			count++;
		}
		cur_inf = cur_inf->next;
	}
	return (count);
}

static int	ft_do_hd(t_data *data)
{
	t_cmd	*cur_cmd;
	int		i;

	i = 0;
	cur_cmd = data->cmd_list;
	while (cur_cmd != NULL && i < data->hdnum)
	{
		i += ft_execute_hd(data, cur_cmd, data->fd_hd, i);
		if (i == data->hdnum)
			return (SUCCESS);
		else
			cur_cmd = cur_cmd->next;
	}
	return (FAIL);
}

static int	ft_exec_heredocs(t_data *data)
{
	data->hdnum = ft_get_hd_nb(data->cmd_list);
	if (data->hdnum == 0)
		return (SUCCESS);
	data->fd_hd = malloc(sizeof(int) * data->hdnum);
	if (!data->fd_hd)
		return (FAIL);
	data->hd_files = ft_create_hd_filenames(data->hdnum);
	if (!data->hd_files)
		return (FAIL);
	ft_set_heredoc_files(data);
	ft_do_hd(data);
	return (SUCCESS);
}

int	ft_launch_heredoc(t_data *data)
{
	if (ft_exec_heredocs(data) == FAIL)
	{
		if (ft_is_error_to_print(data->token_list) == NO)
			ft_pipe_at_end_error_check(data->token_list);
		return (FAIL);
	}
	if (ft_is_error_to_print(data->token_list) == YES)
		return (FAIL);
	if (ft_pipe_at_end_error_check(data->token_list) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
