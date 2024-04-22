/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:24:42 by allblue           #+#    #+#             */
/*   Updated: 2024/04/22 17:34:36 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

static void	ft_print_value(t_arg *cur, int fd)
{
	if (cur->value == NULL)
		ft_putstr_fd(" ", fd);
	else
		ft_putstr_fd(cur->value, fd);
	if (cur->next)
		ft_putstr_fd(" ", fd);
}

int	ft_echo(t_data *data, t_cmd *cmd)
{
	t_arg	*cur;
	int		fd;

	cur = cmd->arg_list;
	if (!cur || !cur->value)
		return (FAIL);
	fd = ft_get_fd_out(data, cmd);
	cur = ft_skip_options(cur->next);
	while (cur)
	{
		ft_print_value(cur, fd);
		cur = cur->next;
	}
	if (ft_should_i_add_nl(cmd->arg_list) == YES)
		ft_putstr_fd("\n", fd);
	if (fd != STDOUT_FILENO)
		close(fd);
	return (0);
}
