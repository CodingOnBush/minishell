/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   single_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 15:46:13 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/04 16:03:09 by vvaudain         ###   ########.fr       */
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
	if (execve(path_name, cmd->args, data->env) != -1)
		exit(0);
	perror(path_name);
	ft_free_exec(data);
	free(path_name);
	exit(126);
}

void	exec_single_command(t_data *data)
{
	int		fd_in;
	int		fd_out;
	int		exit_status;
	char 	*infile;
	char	*outfile;
	t_cmd	*cmd_to_exec;
	
	infile = NULL;
	outfile = NULL;
	cmd_to_exec = data->cmd_list;
	if (is_infile(cmd_to_exec) == YES)
	{
		infile = get_missing_file(cmd_to_exec->infile_list);
		if (infile == NULL)
		{
			infile = get_last_infile(cmd_to_exec->infile_list);
			// fd_in = open(infile, O_RDONLY);
		}
		else
			return (perror(infile));
	}
	else
			fd_in = STDIN_FILENO;
	if (cmd_to_exec->outfile_list != NULL)
	{
		outfile = get_last_outfile(cmd_to_exec->outfile_list);
	}
	else
		fd_out = STDOUT_FILENO;
	if (cmd_to_exec->arg_list && ft_isbuiltin(cmd_to_exec->arg_list->value) == YES)
	{
		printf("builtin\n");
		ft_exec_builtin(data, cmd_to_exec);
		// if (ft_exec_builtin(data, cmd_to_exec) == FAIL)
		// 	printf("error\n");
		// else
			// builtin success
	}
	else	
	{
		printf("execve\n");
		ft_single_exec(data, cmd_to_exec);
		// free(data->join_path); --> je le fais dans pipex mais jsp si necessaire ici --> a voir
	}
}
