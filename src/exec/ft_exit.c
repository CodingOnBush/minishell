/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:40:03 by ubuntu            #+#    #+#             */
/*   Updated: 2024/04/23 10:19:03 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static long long	ft_atoll(char *str)
{
	long long	result;
	int			sign;

	result = 0;
	sign = 1;
	while (ft_is_space(*str) == YES)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result * sign);
}

int	ft_exit(t_data *data, t_arg *arg_list)
{
	int		status;
	char	*str;

	status = data->exit_status;
	if (arg_list->next != NULL)
	{
		str = arg_list->next->value;
		if (ft_isnumber(str) == NO || (ft_isnumber(str) == YES && ft_atoll(str) > LLONG_MAX))
		{
			ft_putstr_fd("exit\nminishell: exit: ", 2);
			ft_putstr_fd(str, 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			ft_free_all(data);
			exit(2);
		}
		status = ft_atoll(str) % 256;
	}
	ft_putstr_fd("exit\n", 1);
	data->exit_builtin = YES;
	ft_free_all(data);
	exit(status);
	return (status);
}
