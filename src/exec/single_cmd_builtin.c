/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd_builtin.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 10:47:59 by momrane           #+#    #+#             */
/*   Updated: 2024/04/24 12:52:21 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static int	ft_is_infile(t_cmd *cmd)
// {
// 	t_infile	*cur_inf;

// 	cur_inf = cmd->infile_list;
// 	while (cur_inf != NULL)
// 	{
// 		if (cur_inf->filename != NULL)
// 			return (YES);
// 		cur_inf = cur_inf->next;
// 	}
// 	return (0);
// }

// static char	*ft_get_missing_file(t_infile *inf_list)
// {
// 	t_infile	*cur_inf;

// 	cur_inf = inf_list;
// 	while (cur_inf != NULL)
// 	{
// 		if (access(cur_inf->filename, F_OK) == -1)
// 			return (cur_inf->filename);
// 		cur_inf = cur_inf->next;
// 	}
// 	return (NULL);
// }

// static char	*ft_get_last_infile(t_infile *inf_list)
// {
// 	t_infile	*cur_inf;
// 	t_infile	*last_infile;

// 	cur_inf = inf_list;
// 	while (cur_inf != NULL)
// 	{
// 		if (cur_inf->filename != NULL)
// 			last_infile = cur_inf;
// 		cur_inf = cur_inf->next;
// 	}
// 	return (last_infile->filename);
// }

// static char	*ft_get_valid_infile(t_data *data, t_cmd *cmd)
// {
// 	char	*infile;

// 	(void)data;
// 	infile = NULL;
// 	if (ft_is_infile(cmd) == NO)
// 		return (NULL);
// 	infile = ft_get_missing_file(cmd->infile_list);
// 	if (infile != NULL)
// 	{
// 		ft_putstr_fd("minishell: ", STDERR_FILENO);
// 		perror(infile);
// 		return (NULL);
// 	}
// 	infile = ft_get_last_infile(cmd->infile_list);
// 	return (infile);
// }

// static int	ft_get_fdin(t_data *data, t_cmd *cmd)
// {
// 	char	*infile;
// 	int		fd_in;

// 	fd_in = STDIN_FILENO;
// 	infile = ft_get_valid_infile(data, cmd);
// 	if (cmd->infile_list != NULL && infile == NULL)
// 		return (-1);
// 	if (infile != NULL)
// 	{
// 		fd_in = open(infile, O_RDONLY);
// 		if (fd_in == -1)
// 		{
// 			ft_putstr_fd("minishell: ", STDERR_FILENO);
// 			perror(infile);
// 			ft_reset_data(data);
// 			return (-1);
// 		}
// 	}
// 	return (fd_in);
// }

// static t_outfile	*get_last_outfile(t_outfile *out_list)
// {
// 	t_outfile	*cur;
// 	int			fd;

// 	cur = out_list;
// 	if (!cur)
// 		return (NULL);
// 	while (cur->next != NULL)
// 	{
// 		if (access(cur->filename, F_OK) == -1)
// 		{
// 			if (cur->append == true)
// 				fd = open(cur->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 			else
// 				fd = open(cur->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 			if (fd != -1 && fd != STDOUT_FILENO)
// 				close(fd);
// 		}
// 		cur = cur->next;
// 	}
// 	return (cur);
// }

// static int	ft_get_fdout(t_data *data, t_cmd *cmd)
// {
// 	t_outfile	*outfile;
// 	int			fd_out;

// 	(void)data;
// 	fd_out = STDOUT_FILENO;
// 	outfile = get_last_outfile(cmd->outfile_list);
// 	if (!outfile)
// 		return (fd_out);
// 	if (outfile != NULL && outfile->append == YES)
// 		fd_out = open(outfile->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
// 	else if (outfile != NULL && outfile->append == NO)
// 		fd_out = open(outfile->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
// 	if (fd_out == -1)
// 	{
// 		ft_putstr_fd("minishell: ", STDERR_FILENO);
// 		perror(outfile->filename);
// 		return (-1);
// 	}
// 	return (fd_out);
// }

int	ft_exec_single_builtin(t_data *data)
{
	t_cmd	*cmd;
	// int		fdin;
	// int		fdout;
	t_redir	*redir;
	int		fdin_save;
	int		fdout_save;

	cmd = data->cmd_list;
	if (cmd == NULL || cmd->arg_list == NULL)
		return (data->exit_status);
	redir = ft_get_redirs(data, cmd);
	if (redir == NULL)
	{
		ft_reset_data(data);
		free(redir);
		return(data->exit_status);
	}
	// fdin = ft_get_fdin(data, cmd);
	if (redir->fd_in == -1)
		return (1);
	// fdout = ft_get_fdout(data, cmd);
	if (redir->fd_out == -1)
	{
		if (redir->fd_in != STDIN_FILENO)
			close(redir->fd_in);
		return (1);
	}
	fdin_save = dup(STDIN_FILENO);
	fdout_save = dup(STDOUT_FILENO);
	dup2(redir->fd_in, STDIN_FILENO);
	dup2(redir->fd_out, STDOUT_FILENO);
	if (redir->fd_in != STDIN_FILENO)
		close(redir->fd_in);
	if (redir->fd_out != STDOUT_FILENO)
		close(redir->fd_out);
	data->exit_status = ft_exec_builtin(data, cmd);
	dup2(fdin_save, STDIN_FILENO);
	dup2(fdout_save, STDOUT_FILENO);
	close(fdin_save);
	close(fdout_save);
	free(redir);
	return (data->exit_status);
}
