/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 09:40:03 by ubuntu            #+#    #+#             */
/*   Updated: 2024/04/23 15:05:30 by vvaudain         ###   ########.fr       */
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

static int ft_is_too_big(char *str)
{
	if (ft_strlen(str) > 19)
		return (YES);
	if (ft_isnumber(str) == YES && ft_atoll(str) > LLONG_MAX)
		return (YES);
	return (NO);
}

static int	ft_arg_number(t_arg *arg_list)
{
	int	i;

	i = 0;
	while (arg_list != NULL)
	{
		i++;
		arg_list = arg_list->next;
	}
	return (i);
}

static void ft_error(t_data *data, char *arg, char *str, int status)
{
	ft_putstr_fd("exit\nminishell: exit: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(str, 2);
	ft_free_all(data);
	exit(status);
}

int	ft_exit(t_data *data, t_arg *arg_list)
{
	int		status;
	char	*str;

	status = data->exit_status;
	if (arg_list->next != NULL)
	{
		str = arg_list->next->value;
		if (ft_isnumber(str) == NO || ft_is_too_big(str) == YES)
			ft_error(data, str, ": numeric argument required\n", 2);
		else if (ft_arg_number(arg_list) > 2)
			ft_error(data, str, ": too many arguments\n", 1);
		status = ft_atoll(str) % 256;
	}
	ft_putstr_fd("exit\n", 1);
	data->exit_builtin = YES;
	ft_free_all(data);
	exit(status);
	return (status);
}
