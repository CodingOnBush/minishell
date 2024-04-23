/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 01:14:13 by allblue           #+#    #+#             */
/*   Updated: 2024/04/22 17:34:36 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_token	*ft_findlast_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

static int	is_error(t_token *list, t_token *token)
{
	if (!list || !token)
		return (NO);
	if (token->next == NULL && ft_isop(token->value) == NO && token->type != PIPE)
		return (NO);
	if (ft_isop(token->value) == YES && !token->next)
		return (assign_error(token, NEWLINE_ERROR), YES);
	if (ft_isop(token->value) == YES && token->next && ft_isop(token->next->value) == YES)
		return (assign_error(token, token->next->type), YES);
	// if (ft_isop(token->value) == YES && token->next == NULL)
	// 	return (assign_error(token, NEWLINE_ERROR), YES);
	if (token->type == PIPE)
	{
		if (token->next && ft_isop(token->next->value) == YES)
		{
			if (token->next->next && token->next->next->type == PIPE)
				return (assign_error(token->next, token->next->next->type), YES);
			else if (ft_isop(token->next->value) == YES && token->next->next == NULL)
				return (assign_error(token->next, NEWLINE_ERROR), YES);
		}
		return (NO);
	}
	if (ft_isop(token->value) == YES && token->next != NULL && token->next->type == PIPE)
		return (assign_error(token, token->next->type), YES);
	if (ft_isoperator(token->value) >= 1 && token->next == NULL)
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

static int ft_double_pipe_detected(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE && token->next && token->next->type == PIPE)
			return (YES);
		token = token->next;
	}
	return (NO);
}

int	ft_check_token_list(t_token *list)
{
	t_token	*cur_token;
	t_token	*last_token;

	cur_token = list;
	if (!cur_token)
		return (SUCCESS);
	last_token = ft_findlast_token(list);
	if (ft_double_pipe_detected(cur_token) == YES)
		return (ft_print_error(DOUBLE_PIPE_ERROR), FAIL);
	if (cur_token->value && cur_token->value[0] == '|')
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