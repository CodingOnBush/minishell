/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:48:50 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/24 16:02:58 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	writing_loop(t_data *data, int fd_hd, char *delimiter,
		bool to_expand)
{
	char	*line;
	size_t	len;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("warning: here-document delimited by end of file\n",
				2);
			break ;
		}
		if (to_expand == true)
			line = ft_get_expanded_str(data, line);
		line = ft_super_strjoin(line, ft_strdup("\n"));
		len = ft_strlen((const char *)line);
		if (ft_strncmp(line, delimiter, len - 1) == 0)
			break ;
		else
		{
			write(fd_hd, line, len);
			free(line);
		}
	}
	free(line);
}

static void	ft_set_hd_as_infiles(t_data *data)
{
	t_infile	*lst;
	t_cmd		*cur;
	int			i;

	i = 0;
	cur = data->cmd_list;
	if (!cur)
		return ;
	while (cur)
	{
		lst = cur->infile_list;
		while (lst)
		{
			if (lst->delimiter != NULL && data->hd_files != NULL
				&& data->hd_files[i] != NULL)
			{
				lst->filename = data->hd_files[i++];
				if (!lst->filename)
					return ;
			}
			lst = lst->next;
		}
		cur = cur->next;
	}
}

static int	execute_hd(t_data *data, t_cmd *cmd, int *fd_hd, int i)
{
	t_infile	*cur_inf;
	int			count;

	cur_inf = cmd->infile_list;
	count = 0;
	ft_set_hd_as_infiles(data);
	while (cur_inf != NULL && (i + count) < data->hdnum)
	{
		if (cur_inf->delimiter != NULL)
		{
			fd_hd[i + count] = open(data->hd_files[i + count],
					O_WRONLY | O_CREAT, 0644);
			if (fd_hd[i + count] == -1)
				return (ft_print_error(HDEXEC), ft_free_all(data), FAIL);
			writing_loop(data, fd_hd[i + count], cur_inf->delimiter,
				cur_inf->to_expand);
			close(fd_hd[i + count]);
			count++;
		}
		cur_inf = cur_inf->next;
	}
	return (count);
}

static int	do_heredocs(t_data *data)
{
	t_cmd	*cur_cmd;
	int		i;

	data->hdnum = get_hd_number(data->cmd_list);
	if (data->hdnum == 0)
		return (SUCCESS);
	i = 0;
	data->fd_hd = malloc(sizeof(int) * data->hdnum);
	if (!data->fd_hd)
		return (FAIL);
	data->hd_files = create_hd_files(data->hdnum);
	if (!data->hd_files)
		return (FAIL);
	cur_cmd = data->cmd_list;
	while (cur_cmd != NULL && i < data->hdnum)
	{
		i += execute_hd(data, cur_cmd, data->fd_hd, i);
		if (i == data->hdnum)
			return (SUCCESS);
		else
			cur_cmd = cur_cmd->next;
	}
	return (FAIL);
}

int	ft_launch_heredoc(t_data *data)
{
	if (do_heredocs(data) == FAIL)
	{
		if (is_error_to_print(data->token_list) == NO)
			ft_pipe_at_end_error_check(data->token_list);
		return (FAIL);
	}
	if (is_error_to_print(data->token_list) == YES)
		return (FAIL);
	if (ft_pipe_at_end_error_check(data->token_list) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
