/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:40:03 by ubuntu            #+#    #+#             */
/*   Updated: 2024/04/15 09:50:39 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_isnumber(char *str)
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

int	ft_exit(t_arg *arg_list)
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
	exit(status);
	return (status);
}