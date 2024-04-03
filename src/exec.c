/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/03 17:56:22 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	exec_command(t_data *data, int process, t_cmd *cmd_to_exec)
{
	int		count;
	int		fd_in;
	int		fd_out;

	count = 0;
	if (process == 0)
		fd_in = STDIN_FILENO;
	else
		fd_in = data->pipe_ends[process - 1][0];
	if (process == data->cmd_nb - 1)
		fd_out = STDOUT_FILENO;
	else
		fd_out = data->pipe_ends[process][1];
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	ft_close_pipes(data);
	if (ft_isbuiltin(cmd_to_exec->arg_list->value) == YES)
	{
		if (ft_exec_builtin(data, cmd_to_exec) == FAIL)
			perror(cmd_to_exec->arg_list->value);
		// else
			// builtin success
	}
	else	
	{
		// ft_exec(data, cmd_to_exec);
		// execve(/*la commande avec le chemin*/, /*le tableau arg[]*/, data->env);
		// perror("execve");
		// exit(1);
	}
		//execve
	/* BUILTIN ou EXECVE */
	
}

void	child_process(t_data *data, int process)
{
	t_cmd	*cmd_to_exec;

	cmd_to_exec = data->cmd_list;
	while (process > cmd_to_exec->pos && cmd_to_exec)
		cmd_to_exec = cmd_to_exec->next;
	exec_command(data, process, cmd_to_exec);
}


int	ft_fork(t_data *data)
{
	int	process;
	
	process = -1;
	alloc_ids(data);
	while (++process < data->cmd_nb)
	{
		data->ids[process] = fork();
		if (data->ids[process] == -1)
			return (perror("Forking failed"), FAIL);
		else if (data->ids[process] == 0)
		{
			child_process(data, process);
			ft_free_all(data);
			printf("child process %d\n", process);
			exit(0);
		}
		process++;
		if (process < data->cmd_nb)
		{
			data->ids[process] = fork();
			if (data->ids[process] < 0)
				return (perror("Forking failed"), FAIL);
			else if (data->ids[process] == 0)
			{
				child_process(data, process);
				ft_free_all(data);
				printf("child process %d\n", process);
				exit (0);
			}
		}
	}
	ft_close_pipes(data);
	return (SUCCESS);
}

int	do_pipes(t_data *data)
{
	int		count;
	
	count = 0;
	alloc_pipes(data);
	while (count < data->cmd_nb - 1)
	{
		if (pipe(data->pipe_ends[count]) == -1)
		{
			perror(NULL);
			//free data->pipe_ends
			return (FAIL);
		}
		count++;
	}
	return (SUCCESS);
}

int	ft_start_exec(t_data *data)
{
	data->cmd_nb = get_cmd_nb(data->cmd_list);
	if (do_pipes(data) == FAIL)
		return (FAIL);
	else
		ft_fork(data);
	
	return (SUCCESS);
}
