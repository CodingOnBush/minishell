/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/14 15:24:42 by allblue           #+#    #+#             */
/*   Updated: 2024/04/16 13:00:46 by allblue          ###   ########.fr       */
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

int	ft_echo(t_arg *lst)
{
	bool	n_flag;

	if (!lst || !lst->value)
		return (FAIL);
	n_flag = false;
	if (lst->next && ft_is_n(lst->next->value) == YES)
		n_flag = true;
	lst = ft_get_first_arg_to_print(lst->next);
	while (lst)
	{
		printf("%s", lst->value);
		lst = lst->next;
		if (lst)
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
	return (0);
}
