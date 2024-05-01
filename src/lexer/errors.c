/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:36:56 by vvaudain          #+#    #+#             */
/*   Updated: 2024/05/01 16:43:31 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pipe_at_end_error_check(t_token *list)
{
	t_token	*cur_token;

	cur_token = list;
	while (cur_token->next != NULL)
	{
		if (cur_token->pipe_at_end == true && cur_token->next->type == PIPE
			&& cur_token->next->next == NULL)
		{
			ft_print_err(PIPE);
			return (FAIL);
		}
		cur_token = cur_token->next;
	}
	return (SUCCESS);
}

void	ft_err(t_token *token, int err_type)
{
	if (err_type == PIPE_AT_END)
		token->pipe_at_end = true;
	else
	{
		token->error = true;
		token->err_type = err_type;
	}
}

void	ft_print_err(int errno)
{
	if (errno == APPEND)
		ft_putstr_fd("minishell: syntax error near unexpected token `>>'\n", 2);
	else if (errno == HD)
		ft_putstr_fd("minishell: syntax error near unexpected token `<<'\n", 2);
	else if (errno == RIGHT_TRUNC)
		ft_putstr_fd("minishell: syntax error near unexpected token `>'\n", 2);
	else if (errno == LT)
		ft_putstr_fd("minishell: syntax error near unexpected token `<'\n", 2);
	else if (errno == PIPE)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (errno == NEWLINE_ERROR)
		ft_putstr_fd("minishell: syntax error near unexpected token `newline'\n",
			2);
	else if (errno == QUOTES_ERROR)
		ft_putstr_fd("minishell: unclosed single or double quote\n", 2);
	else if (errno == DOUBLE_PIPE_ERROR)
		ft_putstr_fd("minishell: syntax error near unexpected token `|'\n", 2);
	else if (errno == HDEXEC)
		ft_putstr_fd("minishell: heredoc execution failed\n", 2);
}
