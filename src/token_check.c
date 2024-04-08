/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:27:38 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/07 14:49:14 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_error(t_token *list, t_token *token)
{
	if (!list || !token)
		return (NO);
	if (token->next == NULL && ft_isop(token->str) == NO && token->type != PIPE)
		return (NO);
	if (ft_isop(token->str) == YES && !token->next)
		return (assign_error(token, NEWLINE_ERROR), YES);
	if (ft_isop(token->str) == YES && token->next && ft_isop(token->next->str) == YES)
		return (assign_error(token, token->next->type), YES);
	// if (ft_isop(token->str) == YES && token->next == NULL)
	// 	return (assign_error(token, NEWLINE_ERROR), YES);
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
	if (ft_isop(token->str) == YES && token->next != NULL && token->next->type == PIPE)
		return (assign_error(token, token->next->type), YES);
	if (ft_isoperator(token->str) >= 1 && token->next == NULL)
		return (assign_error(token, NEWLINE_ERROR), YES);
	return (NO);
}

static t_token	*token_before_last(t_token *list)
{
	t_token	*cur_token;

	cur_token = list;
	while (cur_token->next->next != NULL)
		cur_token = cur_token->next;
	return (cur_token);
}

// rename because it checks errors and set errors variables
int	check_token_list(t_token *list)
{
	t_token	*cur_token;
	t_token	*last_token;

	cur_token = list;
	if (!cur_token)
		return (SUCCESS);
	last_token = ft_findlast_token(list);
	if (ft_double_pipe_detected(cur_token) == YES)
		return (ft_print_error(DOUBLE_PIPE_ERROR), FAIL);
	if (cur_token->str && cur_token->str[0] == '|')
		return (ft_print_error(PIPE), FAIL);
	while (cur_token != NULL)
	{
		if (is_error(list, cur_token) == YES)
			break ;
		cur_token = cur_token->next;
	}
	if (cur_token == NULL)
	{
		if (last_token->type == PIPE)
			return (assign_error(token_before_last(list), PIPE_AT_END), SUCCESS);
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
