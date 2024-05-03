/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:32:07 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 12:32:08 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_is_n(char *str)
{
	while (*str && ft_is_space(*str) == YES)
		str++;
	if (!str || *str != '-')
		return (NO);
	str++;
	while (*str && *str == 'n')
		str++;
	while (*str && ft_is_space(*str) == YES)
		str++;
	if (*str == '\0')
		return (YES);
	return (NO);
}

static int	ft_should_i_add_nl(t_arg *lst)
{
	if (lst && lst->next && ft_is_n(lst->next->value) == YES)
		return (NO);
	return (YES);
}

static t_arg	*ft_skip_options(t_arg *lst)
{
	t_arg	*cur;

	cur = lst;
	while (cur && ft_is_n(cur->value) == YES)
		cur = cur->next;
	return (cur);
}

static void	ft_print_value(t_arg *cur)
{
	if (cur->value == NULL)
		ft_putstr_fd(" ", 1);
	else
		ft_putstr_fd(cur->value, 1);
	if (cur->next)
		ft_putstr_fd(" ", 1);
}

int	ft_echo(t_data *data, t_cmd *cmd)
{
	t_arg	*cur_arg;

	(void)data;
	cur_arg = cmd->arg_list;
	if (!cur_arg || !cur_arg->value)
		return (FAIL);
	cur_arg = ft_skip_options(cur_arg->next);
	while (cur_arg)
	{
		ft_print_value(cur_arg);
		cur_arg = cur_arg->next;
	}
	if (ft_should_i_add_nl(cmd->arg_list) == YES)
		ft_putstr_fd("\n", 1);
	return (0);
}
