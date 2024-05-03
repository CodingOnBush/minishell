/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:32:25 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 12:32:26 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_status(t_data *data)
{
	data->exit_status = 2;
}

static int	ft_first_checks(t_data *data, t_token *token)
{
	if (token->next == NULL && ft_isop(token->value) == NO
		&& token->type != PIPE)
		return (NO);
	if (ft_isop(token->value) == YES && token->next
		&& ft_isop(token->next->value) == YES)
		return (ft_err(token, token->next->type), ft_status(data), YES);
	if (ft_isop(token->value) == YES && token->next == NULL)
		return (ft_err(token, NEWLINE_ERROR), ft_status(data), YES);
	return (SKIP);
}

static int	ft_is_error(t_data *data, t_token *list, t_token *tok)
{
	int	return_value;

	if (!list || !tok)
		return (NO);
	return_value = ft_first_checks(data, tok);
	if (return_value != SKIP)
		return (return_value);
	if (tok->type == PIPE)
	{
		if (tok->next && ft_isop(tok->next->value) == YES)
		{
			if (tok->next->next && tok->next->next->type == PIPE)
				return (ft_err(tok->next, tok->next->next->type),
					ft_status(data), YES);
			else if (ft_isop(tok->next->value) == YES
				&& tok->next->next == NULL)
				return (ft_err(tok->next, NEWLINE_ERROR), ft_status(data), YES);
		}
	}
	if (ft_isop(tok->value) == YES && tok->next != NULL
		&& tok->next->type == PIPE)
		return (ft_err(tok, tok->next->type), ft_status(data), YES);
	if (ft_isoperator(tok->value) >= 1 && tok->next == NULL)
		return (ft_err(tok, NEWLINE_ERROR), ft_status(data), YES);
	return (NO);
}

static int	ft_double_pipe_detected(t_data *data, t_token *token)
{
	while (token)
	{
		if (token->type == PIPE && token->next && token->next->type == PIPE)
			return (ft_status(data), YES);
		token = token->next;
	}
	return (NO);
}

int	ft_check_token_list(t_data *data, t_token *list)
{
	t_token	*cur_token;
	t_token	*last_token;

	cur_token = list;
	if (!cur_token)
		return (SUCCESS);
	last_token = ft_findlast_token(list);
	if (ft_double_pipe_detected(data, cur_token) == YES)
		return (ft_print_err(DOUBLE_PIPE_ERROR), FAIL);
	if (cur_token->value && cur_token->value[0] == '|')
		return (ft_print_err(PIPE), ft_status(data), FAIL);
	while (cur_token != NULL)
	{
		if (ft_is_error(data, list, cur_token) == YES)
			break ;
		cur_token = cur_token->next;
	}
	if (cur_token == NULL)
	{
		if (last_token->type == PIPE)
			return (ft_err(ft_token_before_last(list), PIPE_AT_END), SUCCESS);
	}
	return (SUCCESS);
}
