/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:27:38 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/21 17:23:46 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_error_messages(int errno)
{
	if (errno == APPEND)
		ft_putstr_fd("syntax error near unexpected token `>>'\n", 2);
	else if (errno == HEREDOC)
		ft_putstr_fd("syntax error near unexpected token `<<'\n", 2);
	else if (errno == RTRUNC)
		ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
	else if (errno == LTRUNC)
		ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
	else if (errno == PIPE)
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	else if (errno == NEWLINE_ERROR)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else if (errno == QUOTES_ERROR)
		ft_putstr_fd("Unclosed single or double quote\n", 2);
}

static int	is_double_pipe(int next_type)
{
	if (next_type == PIPE)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (FAIL);
	}
	else
		return (SUCCESS);
}

static int	check_mutiple_op(t_token *list, t_token *token)
{
	if (!list || !token)
		return (FAIL);
	if (token->next == NULL)
		return (SUCCESS);
	if (token->type == PIPE)
	{
		if (is_double_pipe(token->next->type) == FAIL)
			return (FAIL);
		if ((token->next->type == APPEND || token->next->type == LTRUNC
				|| token->next->type == RTRUNC
				|| token->next->type == RTRUNC) && token->next->next)
		{
			if (ft_isoperator(token->next->next->str) != 0)
			{
				ft_error_messages(token->next->next->type);
				return (FAIL);
			}
		}
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
	if (cur_token->str[0] == '|')
		return (ft_error_messages(PIPE), FAIL);
	while (cur_token != NULL)
	{
		check = check_mutiple_op(list, cur_token);
		if (check == FAIL)
			return (FAIL);
		cur_token = cur_token->next;
	}
	return (SUCCESS);
}
