/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:48:50 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/12 10:20:17 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*get_file_name(int i)
{
	char	*file_num;
	char	*file_name;
	char	*tmp;

	file_name = NULL;
	file_num = NULL;
	file_num = ft_itoa(i);
	file_name = ft_strjoin("tmp_hd", file_num);
	if (!file_name)
		return (NULL);
	if (access(file_name, F_OK) == 0)
	{
		free(file_name);
		tmp = ft_strjoin(file_num, "_");
		if (!tmp)
			return (free(file_num), NULL);
		file_name = ft_strjoin("tmp_hd", tmp);
		if (!file_name)
			return (free(tmp), free(file_num), NULL);
		free(tmp);
	}
	if (file_num)
		free(file_num);
	return (file_name);
}

static char	**create_hd_files(int hdnum)
{
	char	**hd_files;
	int		i;

	hd_files = malloc(sizeof(char *) * (hdnum + 1));
	if (!hd_files)
		return (NULL);
	i = 0;
	while (i < hdnum)
	{
		hd_files[i] = get_file_name(i);
		i++;
	}
	hd_files[i] = NULL;
	return (hd_files);
}

void	writing_loop(t_data *data, int fd_hd, char *delimiter)
{
	char	*line;
	size_t	len;

	(void)data;
	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("warning: here-document delimited by end of file\n",
				2);
			break ;
		}
		len = ft_strlen((const char *)line);
		if (ft_strncmp(line, delimiter, len) == 0)
			break ;
		else
		{
			write(fd_hd, line, len);
			free(line);
		}
	}
	free(line);
}

static int	execute_hd(t_data *data, t_cmd *cmd, int *fd_hd, int i)
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
					O_WRONLY | O_CREAT, 0644);
			if (fd_hd[i + count] == -1)
				return (ft_print_error(HDEXEC), ft_free_all(data), FAIL);
			writing_loop(data, fd_hd[i + count], cur_inf->delimiter);
			close(fd_hd[i + count]);
			count++;
		}
		cur_inf = cur_inf->next;
	}
	return (count);
}

int	do_heredocs(t_data *data)
{
	t_cmd	*cur_cmd;
	int		i;

	data->hdnum = get_hd_number(data->cmd_list);
	printf("hdnum = %d\n", data->hdnum);
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

static int	is_error_to_print(t_data *data, t_token *list)
{
	t_token	*cur_token;

	cur_token = list;
	while (cur_token != NULL)
	{
		if (cur_token->error == true)
		{
			ft_print_error(cur_token->err_type);
			return (ft_free_exec(data), YES);
		}
		cur_token = cur_token->next;
	}
	return (NO);
}

int	ft_launch_heredoc(t_data *data)
{
	if (do_heredocs(data) == FAIL)
	{
		if (is_error_to_print(data, data->token_list) == NO)
			pipe_at_end_error_check(data, data->token_list);
		return (FAIL);
	}
	if (is_error_to_print(data, data->token_list) == YES)
		return (FAIL);
	if (pipe_at_end_error_check(data, data->token_list) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
