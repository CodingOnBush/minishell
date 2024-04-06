/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/06 12:54:00 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_exec(t_data *data, t_cmd *cmd)
{
	char	*path_name;

	path_name = get_cmd_path(data, cmd);
	// printf("path_name = %s\n", path_name);
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
	// printf("execve lletsgo\n");
	execve(path_name, cmd->args, data->env);
	perror(path_name);
	ft_free_exec(data);
	free(path_name);
	exit(126);
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
			if (data->cmd_nb == 1)
				exec_single_command(data);
			else
				child_process(data, process);
			ft_free_all(data);
			exit(0);
		}
	}
	ft_close_pipes(data);
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

int	ft_launch_heredoc(t_data *data)
{
	if (do_heredocs(data) == FAIL)
	{
		if (is_error_to_print(data->token_list) == NO)
			pipe_at_end_error_check(data->token_list);
		return (FAIL);
	}
	if (is_error_to_print(data->token_list) == YES)
		return (FAIL);
	if (pipe_at_end_error_check(data->token_list) == FAIL)
		return (FAIL);
	return (SUCCESS);
}

int	ft_start_exec(t_data *data)
{
	if (ft_launch_heredoc(data) == FAIL)
		return (FAIL);
	if (data->cmd_nb == 1)
	{
		if (ft_isbuiltin(data->cmd_list->arg_list->value) == YES)
			return (ft_exec_builtin(data, data->cmd_list));
		ft_fork(data);
	}
	else if (data->cmd_nb > 1)
	{
		if (do_pipes(data) == FAIL)
			return (FAIL);
		ft_fork(data);
	}
	else if (data->cmd_nb <= 0)
		return (FAIL);
	// ft_fork(data);
	return (SUCCESS);
}
