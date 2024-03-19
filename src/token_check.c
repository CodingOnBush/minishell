/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 15:27:38 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/19 13:53:04 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_error_messages(char *value)
{
	if (ft_isappend(value))
		ft_putstr_fd("syntax error near unexpected token `>>'\n", 2);
	else if (ft_isheredoc(value))
		ft_putstr_fd("syntax error near unexpected token `<<'\n", 2);
	else if (*value == '>')
		ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
	else if (*value == '<')
		ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
	else if (*value == '|')
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
}

static int	is_double_pipe(t_token *list, int next_type)
{
	if (next_type == PIPE)
	{
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		return (ft_free_tokens(&list), FAIL);
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
		if (is_double_pipe(list, token->next->type) == FAIL)
			return (FAIL);
		if ((token->next->type == APPEND || token->next->type == LEFT_TRUNC
				|| token->next->type == RIGHT_TRUNC
				|| token->next->type == RIGHT_TRUNC) && token->next->next)
		{
			if (ft_isoperator(token->next->next->value) != 0)
			{
				ft_error_messages(token->next->next->value);
				return (ft_free_tokens(&list), FAIL);
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
	while (cur_token != NULL)
	{
		check = check_mutiple_op(list, cur_token);
		if (check == FAIL)
			return (FAIL);
		cur_token = cur_token->next;
	}
	return (SUCCESS);
}
