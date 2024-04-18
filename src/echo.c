/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:24:42 by allblue           #+#    #+#             */
/*   Updated: 2024/04/18 16:43:27 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_is_n(char *str)
{
	if (!str || *str != '-')
		return (NO);
	str++;
	while (*str && *str == 'n')
		str++;
	if (*str == '\0')
		return (YES);
	return (NO);
}

static t_arg	*ft_get_first_arg_to_print(t_arg *lst)
{
	t_arg	*cur;

	cur = lst;
	while (cur && ft_is_n(cur->value) == YES)
		cur = cur->next;
	return (cur);
}

int	ft_echo(t_data *data, t_cmd *cmd)
{
	bool	n_flag;
	t_arg	*lst;
	int		fd;

	lst = cmd->arg_list;
	if (!lst || !lst->value)
		return (FAIL);
	fd = ft_get_fd_out(data, cmd);
	n_flag = false;
	if (lst->next && ft_is_n(lst->next->value) == YES)
		n_flag = true;
	lst = ft_get_first_arg_to_print(lst->next);
	while (lst)
	{
		if (lst->value)
			ft_putstr_fd(lst->value, fd);
		else
			ft_putstr_fd(" ", fd);
		lst = lst->next;
		if (lst)
			ft_putstr_fd(" ", fd);
	}
	if (!n_flag)
		ft_putstr_fd("\n", fd);
	close(fd);
	return (0);
}
