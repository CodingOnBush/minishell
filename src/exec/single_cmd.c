/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:46:13 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/24 13:54:39 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_is_infile(t_cmd *cmd)
{
	t_infile	*cur_inf;

	cur_inf = cmd->infile_list;
	while (cur_inf != NULL)
	{
		if (cur_inf->filename != NULL)
			return (YES);
		cur_inf = cur_inf->next;
	}
	return (0);
}

static char	*ft_get_missing_file(t_infile *inf_list)
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

static char	*ft_get_last_infile(t_infile *inf_list)
{
	t_infile	*cur_inf;
	t_infile	*last_infile;

	cur_inf = inf_list;
	while (cur_inf != NULL)
	{
		if (cur_inf->filename != NULL)
			last_infile = cur_inf;
		cur_inf = cur_inf->next;
	}
	return (last_infile->filename);
}

/*
est-ce qu'on devrait pas return 1 au lieu de exit(1) ?
parce que echo < file_does_not_exist ca doit pas quitter
le shell
*/

static char	*ft_get_valid_infile(t_data *data, t_cmd *cmd)
{
	char	*infile;

	infile = NULL;
	if (ft_is_infile(cmd) == NO)
		return (NULL);
	infile = ft_get_missing_file(cmd->infile_list);
	if (infile != NULL)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		perror(infile);
		ft_free_all(data);
		exit(1);
	}
	infile = ft_get_last_infile(cmd->infile_list);
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

void	ft_exec_single_cmd(t_data *data)
{
	t_cmd	*cmd;
	t_redir	*redir;
	int		exit_status;

	cmd = data->cmd_list;
	if (cmd == NULL || cmd->arg_list == NULL)
		return ;
	redir = ft_get_redirs(data, cmd);
	if (redir == NULL)
	{
		exit_status = data->exit_status;
		ft_free_all(data);
		exit(exit_status);
	}
	dup2(redir->fd_in, STDIN_FILENO);
	dup2(redir->fd_out, STDOUT_FILENO);
	if (redir->fd_in != STDIN_FILENO)
		close(redir->fd_in);
	if (redir->fd_out != STDOUT_FILENO)
		close(redir->fd_out);
	free(redir);
	ft_execve(data, cmd);
}
