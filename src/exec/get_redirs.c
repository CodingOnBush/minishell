/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:57:23 by vvaudain          #+#    #+#             */
/*   Updated: 2024/05/02 09:53:58 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_redir	*ft_create_redir(void)
{
	t_redir	*redir;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->fd_in = STDIN_FILENO;
	redir->fd_out = STDOUT_FILENO;
	redir->infile = NULL;
	redir->outfile = NULL;
	return (redir);
}

static int	ft_open_files(t_data *data, t_redir *redir, int is_append)
{
	if (redir->infile)
	{
		redir->fd_in = open(redir->infile, O_RDONLY);
		if (redir->fd_in == -1 || redir->fd_in > FDMAX)
		{
			data->exit_status = 1;
			return (ft_putstr_fd("minishell : ", 2), perror(redir->infile),
				free(redir), FAIL);
		}
	}
	if (redir->outfile)
	{
		if (is_append == YES)
			redir->fd_out = open(redir->outfile, O_CREAT | O_WRONLY | O_APPEND,
					0644);
		else
			redir->fd_out = open(redir->outfile, O_CREAT | O_WRONLY | O_TRUNC,
					0644);
		if (redir->fd_out == -1 || redir->fd_out > FDMAX)
			return (data->exit_status = 1, close(redir->fd_in),
				perror(redir->outfile), free(redir), FAIL);
	}
	return (SUCCESS);
}

static int	ft_handle_outfiles(t_data *data, t_redir *redir, t_token *cur,
		int is_append)
{
	if (is_append == YES)
		redir->fd_out = open(cur->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else
		redir->fd_out = open(cur->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (redir->fd_out == -1 || redir->fd_out > FDMAX)
	{
		data->exit_status = 1;
		return (ft_putstr_fd("minishell : ", 2), perror(cur->value), FAIL);
	}
	if (redir->fd_out != STDOUT_FILENO)
		close(redir->fd_out);
	redir->outfile = cur->value;
	return (SUCCESS);
}

static int	ft_handle_token(t_data *data, t_token *cur, t_redir *redir,
		t_cmd *cmd)
{
	int	is_append;

	is_append = NO;
	if (cur->is_inf == YES || cur->type == LIM)
	{
		redir->infile = cur->value;
		if (cur->heredoc_file != NULL)
			redir->infile = cur->heredoc_file;
		if (access(redir->infile, F_OK | R_OK) == -1)
		{
			data->exit_status = 1;
			return (ft_putstr_fd("minishell : ", 2), perror(redir->infile),
				FAIL);
		}
	}
	if (cur->is_outf == YES)
	{
		is_append = ft_file_is_append(cmd, cur->value);
		if (is_append == FAIL)
			return (FAIL);
		if (ft_handle_outfiles(data, redir, cur, is_append) == FAIL)
			return (FAIL);
		return (is_append);
	}
	return (NO);
}

t_redir	*ft_get_redirs(t_data *data, t_cmd *cmd)
{
	t_token	*cur;
	t_redir	*redir;
	int		is_append;

	is_append = NO;
	cur = cmd->token_list;
	redir = ft_create_redir();
	if (!redir || !cur)
		return (NULL);
	while (cur != NULL)
	{
		is_append = ft_handle_token(data, cur, redir, cmd);
		if (is_append == FAIL)
			return (free(redir), NULL);
		cur = cur->next;
	}
	if (ft_open_files(data, redir, is_append) == FAIL)
		return (free(redir), NULL);
	return (redir);
}
