/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:27:38 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/26 15:29:26 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

// static int	is_double_pipe(int next_type)
// {
// 	if (next_type == PIPE)
// 	{
// 		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
// 		return (FAIL);
// 	}
// 	else
// 		return (SUCCESS);
// }

static void	check_mutiple_op(t_token *list, t_token *token)
{
	if (!list || !token)
		return ;
	if (token->next == NULL)
		return ;
	if (token->type == PIPE)
	{
		if ((token->next->type == APPEND || token->next->type == LEFT_TRUNC
				|| token->next->type == RIGHT_TRUNC) && token->next->next)
		{
			if (ft_isoperator(token->next->next->str) != NO)
			{
				token->next->next->error = true;
				token->next->next->err_type = token->next->next->type;
				// ft_error_messages(token->next->next->type);
				return ;
			}
		}
	}
	else if (ft_isoperator(token->str) != NO && token->next != NULL && ft_isoperator(token->next->str) != NO)
	{
		token->next->error = true;
		token->next->err_type = token->next->type;
		// return (ft_error_messages(token->next->type), FAIL);
	}
	return ;
}

int	check_token_list(t_token **list)
{
	t_token	*cur_token;

	if (!list || !*list)
		return (FAIL);
	cur_token = *list;
	if (cur_token->str[0] == '|')
		return (ft_error_messages(PIPE), FAIL);
	while (cur_token != NULL)
	{
		check_mutiple_op(*list, cur_token);
		cur_token = cur_token->next;
	}
	return (SUCCESS);
}

int	ft_check_pipe_error(t_token *token_list)
{
	t_token	*next;

	next = NULL;
	while (token_list)
	{
		next = token_list->next;
		if (token_list->type == PIPE && next && next->type == PIPE)
			return (FAIL);
		token_list = next;
	}
	return (SUCCESS);
}
