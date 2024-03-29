/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:27:38 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/29 15:07:29 by vvaudain         ###   ########.fr       */
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

static int	is_error(t_token *list, t_token *token)
{
	if (!list || !token)
		return (NO);
	if (token->next == NULL)
		return (NO);
	if (token->type == PIPE)
	{
		if (token->next && ft_isop(token->next->str) == YES)
		{
			if (token->next->next && token->next->next->type == PIPE)
				return (assign_error(token->next, token->next->next->type), YES);
			else if (ft_isop(token->next->str) == YES && token->next->next == NULL)
				return (assign_error(token->next, NEWLINE_ERROR), YES);
		}
		return (NO);
	}
	else if (ft_isop(token->str) == YES && token->next != NULL && ft_isop(token->next->str) == YES)
		return (assign_error(token->next, token->next->type), YES);
	else if (ft_isop(token->str) == YES && token->next != NULL && token->next->type == PIPE)
		return (assign_error(token, token->next->type), YES);
	else if (ft_isoperator(token->str) >= 1 && token->next == NULL)
		return (assign_error(token, NEWLINE), YES);
	return (NO);
}

int	check_token_list(t_token **list)// rename because it checks errors and set errors variables
{
	t_token	*cur_token;
	t_token	*last_token;

	if (!list || !*list)
		return (FAIL);
	cur_token = *list;
	last_token = ft_findlast_token(*list);
	if (cur_token->str[0] == '|')
		return (ft_error_messages(PIPE), FAIL);
	if (last_token->type == PIPE)
		return (ft_error_messages(PIPE), FAIL);
	while (cur_token != NULL)
	{
		if (is_error(*list, cur_token) == YES)
			break ;
		cur_token = cur_token->next;
	}
	ft_print_token_list(*list);
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
