/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:27:38 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/14 16:29:55 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	check_mutiple_op(t_token *list, int cur_type, int next_type)
{
	if (cur_type == PIPE)
	{
		if (next_type == PIPE)
		{
			ft_putstr_fd("Syntax error : two pipes follow one another\n", 2);
			return (ft_free_tokens(&list), ERROR);
		}
	}
	if (cur_type == APPEND)
	{
		if (next_type == APPEND || next_type == RIGHT_TRUNC)
		{
			ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
			return (ft_free_tokens(&list), ERROR);
		}
	}
	if (cur_type == HERE_DOC)
	{
		if (next_type == HERE_DOC || next_type == LEFT_TRUNC)
			return (ft_free_tokens(&list), ERROR);
	}
	return (SUCCESS);
}

int	check_token_list(t_token *list)
{
	t_token	*cur_token;
	int		check;

	if (!list)
		return (FAIL);
	cur_token = list;
	while (cur_token != NULL)
	{
		check = check_mutiple_op(list, cur_token->type, cur_token->next->type);
		if (check == ERROR)
			return (ERROR);
		cur_token = cur_token->next;
	}
	return (SUCCESS);
}
