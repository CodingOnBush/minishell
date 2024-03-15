/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:27:38 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/15 10:45:05 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	check_mutiple_op(t_token *list, t_token *token)
{
	int	cur_type;
	int	next_type;

	if (!list || !token)
		return (FAIL);
	if (token->next == NULL)
		return (SUCCESS);
	cur_type = token->type;
	next_type = token->next->type;
	if (cur_type == PIPE)
	{
		if (next_type == PIPE)
		{
			ft_putstr_fd("Syntax error : two pipes follow one another\n", 2);
			return (ft_free_tokens(&list), FAIL);
		}
	}
	// if (cur_type == APPEND)
	// {
	// 	if (next_type == APPEND || next_type == RIGHT_TRUNC)
	// 	{
	// 		ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
	// 		return (ft_free_tokens(&list), FAIL);
	// 	}
	// }
	// if (cur_type == HERE_DOC)
	// {
	// 	if (next_type == HERE_DOC || next_type == LEFT_TRUNC)
	// 		return (ft_free_tokens(&list), FAIL);
	// }
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
		check = check_mutiple_op(list, cur_token);
		if (check == FAIL)
			return (FAIL);
		cur_token = cur_token->next;
	}
	return (SUCCESS);
}
