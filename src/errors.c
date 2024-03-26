/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/25 13:36:56 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/25 13:38:25 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	assign_error(t_token *token, int err_type)
{
	token->error = true;
	token->err_type = err_type;
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
}
