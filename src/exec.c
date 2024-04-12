/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/12 14:28:02 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_jump_util(char *str, char c)
{
	int i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i] && str[i] != c)
	{
		if (str[i] != '.')
			return (-1);
		i++;
	}
	return (i);
}

static int ft_cmd_errors_found(t_cmd *cmd)
{
	char	*str;
	int		jump;

	if (!cmd || !cmd->arg_list)
		return (NO);
	str = cmd->arg_list->value;
	if (ft_strchr(str, '/') == NULL)
		return (NO);
	while (*str)
	{
		if (*str == '.')
		{
			jump = ft_jump_util(str, '/');
			if (jump == -1 || jump > 2)
				return (printf("minishell: %s: No such file or directory\n", cmd->arg_list->value), YES);
			str += jump;
		}
		else if (*str == '/')
			str++;
		else
			return (printf("minishell: %s: No such file or directory\n", cmd->arg_list->value), YES);
	}
	return (printf("minishell: %s: Is a directory\n", cmd->arg_list->value), YES);
}

int ft_exec(t_data *data, t_cmd *cmd)
{
	if (ft_cmd_errors_found(cmd) == YES)
	{
		ft_free_all(data);
		exit(127);
	}
	if (cmd->args && cmd->args[0])
		cmd->cmd_path = ft_get_cmd_path(cmd->args[0]);
	if (cmd->cmd_path == NULL)
	{
		if (!cmd->args || !cmd->args[0])
		{
			ft_free_all(data);
			exit(EXIT_FAILURE);
		}
		else if(cmd->args[0][0] == '&' && cmd->args[0][1]  && cmd->args[0][1] == '&') //ne règle pas le cas : qdazd  &&&&&
			ft_putstr_fd("unexpected token '&&'\n", 2);
		else
			cmd_not_found_error(cmd->args[0]);
		ft_free_all(data);
		exit(127);
	}
	execve(cmd->cmd_path, cmd->args, data->env);
	perror(cmd->cmd_path);
	ft_free_all(data);
	exit(126);
}

int ft_fork(t_data *data)
{
	int process;

	alloc_ids(data);
	process = 0;
	while (process < data->cmd_nb)
	{
		data->ids[process] = fork();
		if (data->ids[process] == -1)
			return (perror("Forking failed"), FAIL);
		if (data->ids[process] == 0)
		{
			if (data->cmd_nb == 1)
				ft_exec_single_cmd(data);
			else
				child_process(data, process);
			ft_free_all(data);
			exit(0);
		}
		process++;
	}
	ft_close_pipes(data);
	return (SUCCESS);
}

void ft_wait_for_children(t_data *data)
{
	int status;
	int i;

	i = 0;
	status = 0;
	if (!data->ids)
		return;
	if (data->cmd_nb == 1 && ft_isbuiltin(data->cmd_list))
		return;
	if (waitpid(data->ids[data->cmd_nb - 1], &status, 0) == data->ids[data->cmd_nb - 1])
	{
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status) != 0)
			data->exit_status = SIGNUM + 128;
		else
			data->exit_status = 0;
	}
}

void ft_launch_exec(t_data *data)
{
	if (ft_launch_heredoc(data) == FAIL || data->cmd_nb <= 0)
		return;
	if (data->cmd_nb == 1 && ft_isbuiltin(data->cmd_list) == YES)
		ft_exec_builtin(data, data->cmd_list);
	else if (data->cmd_nb == 1 && ft_isbuiltin(data->cmd_list) == NO)
		ft_fork(data);
	else if (data->cmd_nb > 1 && ft_init_pipes(data) == SUCCESS)
		ft_fork(data);
	ft_wait_for_children(data);
}
