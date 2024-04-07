/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:37:24 by momrane           #+#    #+#             */
/*   Updated: 2024/04/07 14:45:52 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_check_quote_error(char *line)
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

int ft_double_pipe_detected(t_token *token)
{
	while (token)
	{
		if (token->type == PIPE && token->next && token->next->type == PIPE)
			return (YES);
		token = token->next;
	}
	return (NO);
}
