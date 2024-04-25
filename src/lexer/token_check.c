/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 01:14:13 by allblue           #+#    #+#             */
/*   Updated: 2024/04/25 11:07:37 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_first_checks(t_token *token)
{
	if (token->next == NULL && ft_isop(token->value) == NO
		&& token->type != PIPE)
		return (NO);
	if (ft_isop(token->value) == YES && !token->next)
		return (assign_error(token, NEWLINE_ERROR), YES);
	if (ft_isop(token->value) == YES && token->next
		&& ft_isop(token->next->value) == YES)
		return (assign_error(token, token->next->type), YES);
	return (SKIP);
}

static int	is_error(t_token *list, t_token *tok)
{
	int		return_value;

	if (!list || !tok)
		return (NO);
	return_value = ft_first_checks(tok);
	if (return_value != SKIP)
		return (return_value);
	if (tok->type == PIPE)
	{
		if (tok->next && ft_isop(tok->next->value) == YES)
		{
			if (tok->next->next && tok->next->next->type == PIPE)
				return (assign_error(tok->next, tok->next->next->type), YES);
			else if (ft_isop(tok->next->value) == YES
				&& tok->next->next == NULL)
				return (assign_error(tok->next, NEWLINE_ERROR), YES);
		}
		return (NO);
	}
	if (ft_isop(tok->value) == YES && tok->next != NULL
		&& tok->next->type == PIPE)
		return (assign_error(tok, tok->next->type), YES);
	if (ft_isoperator(tok->value) >= 1 && tok->next == NULL)
		return (assign_error(tok, NEWLINE_ERROR), YES);
	return (NO);
}

static int	ft_double_pipe_detected(t_token *token)
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
			return (assign_error(token_before_last(list), PIPE_AT_END),
				SUCCESS);
	}
	return (SUCCESS);
}
