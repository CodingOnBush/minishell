/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:47:50 by momrane           #+#    #+#             */
/*   Updated: 2024/04/26 11:15:33 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_set_delimiters(t_token **token_list)
{
	t_token	*token;

	token = *token_list;
	while (token)
	{
		if (token->type == HERE_DOC && token->next && token->next->type == WORD)
			token->next->type = LIM;
		token = token->next;
	}
}

static int	ft_check_quote_error(char *line)
{
	int	quote;

	quote = 0;
	if (!line)
		return (FAIL);
	while (*line)
	{
		if (ft_isquote(*line) && ft_strchr(line + 1, *line) != NULL)
			line += ft_strchr(line + 1, *line) - line + 1;
		else
		{
			if (ft_isquote(*line))
				quote++;
			line++;
		}
	}
	if (quote % 2 != 0)
		return (FAIL);
	return (SUCCESS);
}

int	ft_lexer(t_data *data)
{
	if (ft_check_quote_error(data->line) == NO)
	{
		data->exit_status = 2;
		return (ft_print_error(QUOTES_ERROR), FAIL);
	}
	data->token_list = ft_create_token_list(data->line);
	if (!data->token_list)
		return (FAIL);
	ft_set_delimiters(&data->token_list);
	if (ft_check_token_list(data, data->token_list) == FAIL)
		return (FAIL);
	ft_expand(data, &data->token_list);
	return (SUCCESS);
}
