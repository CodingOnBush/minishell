/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:48:50 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/29 11:23:13 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	writing_loop(t_data *data, int fd_hd, char *delimiter,
		bool to_expand)
{
	char	*line;
	// size_t	len;

	while (1)
	{
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("warning: here-document delimited by end of file\n", 2);
			break ;
		}
		// printf("line = [%s]\n", line);
		// if (line[0] == '\n')
		// 	printf("JE SAUTE\n");
		if (to_expand == true && ft_strchr(line, '$') != NULL && ft_strcmp(line, delimiter) != 0)
		{
			line = ft_get_expanded_str(data, line);
		}
		// len = ft_strlen((const char *)line);
		// printf("line =      [%s]\n", line);
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

// static void	ft_set_heredoc_file_in_token(t_cmd *cur_cmd, t_infile *cur_inf)
// {
// 	t_token	*cur_token;

// 	cur_token = cur_cmd->token_list;
// 	if (!cur_token)
// 		return ;
// 	while (cur_token)
// 	{
// 		// ATTENTION cat << EOF << EOF << EOF
// 		if (cur_token->type == LIM && ft_strcmp(cur_token->value, cur_inf->delimiter) == 0)
// 		{
// 			cur_token->heredoc_file = cur_inf->filename;
// 			return ;
// 		}
// 		cur_token = cur_token->next;
// 	}
// }

// static void	ft_set_hd_as_infiles(t_data *data)
// {
// 	t_infile	*cur_inf;
// 	t_cmd		*cur_cmd;
// 	int			i;

// 	i = 0;
// 	cur_cmd = data->cmd_list;
// 	if (!cur_cmd)
// 		return ;
// 	while (cur_cmd)
// 	{
// 		cur_inf = cur_cmd->infile_list;
// 		while (cur_inf)
// 		{
// 			if (cur_inf->delimiter != NULL && data->hd_files != NULL && data->hd_files[i] != NULL)
// 			{
// 				cur_inf->filename = data->hd_files[i];
// 				ft_set_heredoc_file_in_token(cur_cmd, cur_inf);
// 				if (!cur_inf->filename)
// 					return ;
// 				i++;
// 			}
// 			cur_inf = cur_inf->next;
// 		}
// 		cur_cmd = cur_cmd->next;
// 	}
// }

static void	ft_print_all_fds(int *fd_hd, int hdnum)
{
	int	i;

	i = 0;
	ft_putstr_fd("int *fd_hd = ", 2);
	while (i < hdnum)
	{
		ft_putnbr_fd(fd_hd[i], 2);
		ft_putstr_fd(", ", 2);
		i++;
	}
	ft_putstr_fd("\n", 2);
}

static int	execute_hd(t_data *data, t_cmd *cmd, int *fd_hd, int i)
{
	t_infile	*cur_inf;
	int			count;

	cur_inf = cmd->infile_list;
	count = 0;
	// ft_set_hd_as_infiles(data);
	while (cur_inf != NULL && (i + count) < data->hdnum)
	{
		if (cur_inf->delimiter != NULL)
		{
			fd_hd[i + count] = open(data->hd_files[i + count],
					O_WRONLY | O_RDONLY | O_CREAT, 0644);
			if (fd_hd[i + count] == -1)
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

	// data->hdnum = ft_get_hd_nb(data->cmd_list);
	// if (data->hdnum == 0)
	// 	return (SUCCESS);
	// data->fd_hd = malloc(sizeof(int) * data->hdnum);
	// if (!data->fd_hd)
	// 	return (FAIL);
	// data->hd_files = ft_create_hd_filenames(data->hdnum);
	// if (!data->hd_files)
	// 	return (FAIL);
	i = 0;
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

static t_infile	*ft_get_next_infile(t_infile *infile, char *name)
{
	t_infile	*cur_inf;

	cur_inf = infile;
	while (cur_inf)
	{
		if (cur_inf->filename == NULL && ft_strcmp(cur_inf->delimiter, name) == 0)
			return (cur_inf);
		cur_inf = cur_inf->next;
	}
	return (NULL);
}

static void	ft_set_heredoc_files(t_data *data)
{
	t_token		*cur_token;
	t_cmd		*cur_cmd;
	t_infile	*infile;
	int			count;

	count = 0;
	cur_cmd = data->cmd_list;
	if (!cur_cmd)
		return ;
	infile = cur_cmd->infile_list;
	while (cur_cmd != NULL && count < data->hdnum)
	{
		cur_token = cur_cmd->token_list;
		while (cur_token)
		{
			if (cur_token->type == HERE_DOC)
			{
				if (cur_token->next && cur_token->next->type == LIM)
				{
					cur_token->next->heredoc_file = data->hd_files[count];
					infile = ft_get_next_infile(infile, cur_token->next->value);
					if (infile)
						infile->filename = data->hd_files[count];
					infile = infile->next;
					count++;
				}
			}
			cur_token = cur_token->next;
		}	
		cur_cmd = cur_cmd->next;
	}
}

int	ft_launch_heredoc(t_data *data)
{
	t_token	*cur_token;
	t_cmd	*cur_cmd;
	int		count;

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
