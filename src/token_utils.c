/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:41:05 by momrane           #+#    #+#             */
/*   Updated: 2024/04/02 17:04:37 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_detect_delimiter(t_token **token_list)
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

void	ft_remove_null_token(t_data *data)
{
	t_token	*token;
	t_token	*tmp;

	token = data->token_list;
	while (token)
	{
		if (token->str == NULL)
		{
			tmp = token->next;
			free(token);
			token = tmp;
		}
		else
			token = token->next;
	}
}
