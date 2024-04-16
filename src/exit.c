/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:40:03 by ubuntu            #+#    #+#             */
/*   Updated: 2024/04/16 09:22:36 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_exit_builtin(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd_list;
	while (cmd)
	{
		if (ft_strncmp(cmd->args[0], "exit", ft_strlen("exit")) == 0)
			return (YES);
		cmd = cmd->next;
	}
	return (NO);
}

static int	ft_isnumber(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (ft_isdigit(str[i]) == NO)
			return (NO);
		i++;
	}
	return (YES);
}

int	ft_exit(t_data *data, t_arg *arg_list)
{
	int		status;
	char	*str;

	status = data->exit_status;
	if (arg_list->next != NULL)
	{
		str = arg_list->next->value;
		if (ft_isnumber(str) == NO)
		{
			ft_putstr_fd("exit\n", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			exit(2);
		}
		status = ft_atoi(str);
	}
	ft_putstr_fd("exit\n", 2);
	data->exit_builtin = YES;
	ft_free_all(data);
	exit(status);
	return (status);
}
