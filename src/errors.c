/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:36:56 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/02 12:14:33 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	pipe_at_end_error_check(t_token *list)
{
	t_token	*cur_token;

	cur_token = list;
	while (cur_token->next != NULL)
	{
		if (cur_token->pipe_at_end == true && cur_token->next->type == PIPE && cur_token->next->next == NULL)
		{
			ft_error_messages(PIPE);
			return (FAIL);
		}
		cur_token = cur_token->next;
	}
	return (SUCCESS);
}

void	assign_error(t_token *token, int err_type)
{
	if (err_type == PIPE_AT_END)
	{
		token->pipe_at_end = true;
		token->err_type = PIPE;
	}
	else
	{
		token->error = true;
		token->err_type = err_type;
	}
}

void	ft_error_messages(int errno)
{
	if (errno == APPEND)
		ft_putstr_fd("syntax error near unexpected token `>>'\n", 2);
	else if (errno == HERE_DOC)
		ft_putstr_fd("syntax error near unexpected token `<<'\n", 2);
	else if (errno == RIGHT_TRUNC)
		ft_putstr_fd("syntax error near unexpected token `>'\n", 2);
	else if (errno == LEFT_TRUNC)
		ft_putstr_fd("syntax error near unexpected token `<'\n", 2);
	else if (errno == PIPE)
		ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
	else if (errno == NEWLINE_ERROR)
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	else if (errno == QUOTES_ERROR)
		ft_putstr_fd("Syntax error : Unclosed single or double quote\n", 2);
	else if (errno == DOUBLE_PIPE_ERROR)
		ft_putstr_fd("Syntax error : Double pipe detected\n", 2);
	else if (errno == HDEXEC)
		ft_putstr_fd("Heredoc execution failed\n", 2);
}
