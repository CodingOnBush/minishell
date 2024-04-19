/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:46:13 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/19 14:53:07 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_get_valid_infile(t_data *data, t_cmd *cmd)
{
	char	*infile;

	infile = NULL;
	if (is_infile(cmd) == NO)
		return (NULL);
	infile = get_missing_file(cmd->infile_list);
	if (infile != NULL)
	{
		perror(infile);
		ft_free_all(data);
		exit(1);
	}
	infile = get_last_infile(cmd->infile_list);
	return (infile);
}

int	ft_get_fd_in(t_data *data, t_cmd *cmd)
{
	char	*infile;
	int		fd_in;

	fd_in = STDIN_FILENO;
	infile = ft_get_valid_infile(data, cmd);
	if (infile != NULL)
		fd_in = open(infile, O_RDONLY);
	if (fd_in == -1)
	{
		perror(infile);
		ft_free_all(data);
		exit(1);
	}
	return (fd_in);
}

int	ft_get_fd_out(t_data *data, t_cmd *cmd)
{
	t_outfile	*outfile;
	int			fd_out;

	fd_out = STDOUT_FILENO;
	outfile = get_last_outfile(cmd->outfile_list);
	if (!outfile)
		return (fd_out);
	if (outfile != NULL && outfile->append == YES)
		fd_out = open(outfile->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (outfile != NULL && outfile->append == NO)
		fd_out = open(outfile->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror(outfile->filename);
		ft_free_all(data);
		exit(1);
	}
	return (fd_out);
}

static void	ft_dup_all(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
}

void	ft_exec_single_cmd(t_data *data)
{
	t_cmd	*cmd;
	int		status;

	cmd = data->cmd_list;
	if (cmd == NULL || cmd->arg_list == NULL)
		return (ft_free_exec(data));
	ft_dup_all(ft_get_fd_in(data, cmd), ft_get_fd_out(data, cmd));
	if (ft_isbuiltin(cmd) == YES)
	{
		status = ft_exec_builtin(data, cmd);
		ft_free_all(data);
		exit(status);
	}
	ft_exec(data, cmd);
}
