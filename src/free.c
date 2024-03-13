/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:18:48 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/13 15:53:48 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_tokens(t_token **list)
{
	t_token	*cur_token;
	t_token	*temp_token;

	if (!list)
		return ;
	cur_token = *list;
	while (cur_token != NULL)
	{
		temp_token = cur_token->next;
		free(cur_token->value);
		free(cur_token);
		cur_token = temp_token;
	}
}