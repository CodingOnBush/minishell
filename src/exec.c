/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/04 15:53:03 by momrane          ###   ########.fr       */
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
	if (cmd_to_exec->arg_list && ft_isbuiltin(cmd_to_exec->arg_list->value) == YES)
	{
		ft_exec_builtin(data, cmd_to_exec);
		// if (ft_exec_builtin(data, cmd_to_exec) == FAIL)
		// 	printf("error\n");
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

static int	is_error_to_print(t_token *list)
{
	t_token	*cur_token;

	cur_token = list;
	while (cur_token != NULL)
	{
		if (cur_token->error == true)
		{
			ft_error_messages(cur_token->err_type);
			return (YES);
		}
		cur_token = cur_token->next;
	}
	return (NO);
}

int	ft_start_exec(t_data *data)
{
	if (do_heredocs(data) == FAIL)
	{
		if (is_error_to_print(data->token_list) == NO)
			pipe_at_end_error_check(data->token_list);
		return (FAIL);
	}
	if (pipe_at_end_error_check(data->token_list) == FAIL)
		return (FAIL);
	if (is_error_to_print(data->token_list) == YES)
		return (FAIL);
	data->cmd_nb = get_cmd_nb(data->cmd_list);
	if (data->cmd_nb == 1)
	{
		exec_command(data, 0, data->cmd_list);
	}
	else if (do_pipes(data) == FAIL)
		return (FAIL);
	else
		ft_fork(data);
	return (SUCCESS);
}
