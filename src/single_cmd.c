/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:46:13 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/05 12:10:31 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_single_exec(t_data *data, t_cmd *cmd)
{
	char	*path_name;

	path_name = get_cmd_path(data, cmd);
	if (!path_name)
	{
		if (!cmd->args && !cmd->args[0])
		{
			ft_free_exec(data);
			exit(EXIT_FAILURE);
		}
		if (cmd->args[0][0] == '/' || ft_strncmp("./", cmd->args[0], 2) == 0)
			perror(cmd->args[0]);
		else
			ft_putstr_fd("command not found\n", 2);
		ft_free_exec(data);
		exit(127);
	}
	execve(path_name, cmd->args, data->env);
	perror(path_name);
	ft_free_exec(data);
	free(path_name);
	exit(126);
}

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
		exit(EXIT_FAILURE);
	}
	return (fd_in);
}

int	ft_get_fd_out(t_data *data, t_cmd *cmd)
{
	t_outfile	*outfile;
	int			fd_out;

	fd_out = STDOUT_FILENO;
	outfile = get_last_outfile(cmd->outfile_list);
	if (outfile != NULL && outfile->append == YES)
		fd_out = open(outfile->filename, O_CREAT | O_WRONLY | O_APPEND, 0644);
	else if (outfile != NULL && outfile->append == NO)
		fd_out = open(outfile->filename, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd_out == -1)
	{
		perror(outfile->filename);
		ft_free_all(data);
		exit(EXIT_FAILURE);
	}
	return (fd_out);
}

void	exec_single_command(t_data *data)
{
	t_cmd	*cmd_to_exec;
	int		fd_out;
	int		fd_in;
	
	cmd_to_exec = data->cmd_list;
	if (cmd_to_exec == NULL || cmd_to_exec->arg_list == NULL)
		return ;
	fd_in = ft_get_fd_in(data, cmd_to_exec);
	fd_out = ft_get_fd_out(data, cmd_to_exec);
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	if (fd_in != STDIN_FILENO)
		close(fd_in);
	if (fd_out != STDOUT_FILENO)
		close(fd_out);
	if (ft_isbuiltin(cmd_to_exec->arg_list->value) == YES)
		ft_exec_builtin(data, cmd_to_exec);
	else
		ft_single_exec(data, cmd_to_exec);
}
