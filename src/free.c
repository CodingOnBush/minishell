/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:18:48 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/21 16:24:31 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_tokens(t_token **token_list)
{
	t_token	*cur_token;
	t_token	*temp_token;

	if (*token_list == NULL)
		return ;
	cur_token = *token_list;
	while (cur_token != NULL)
	{
		temp_token = cur_token->next;
		free(cur_token->str);
		free(cur_token);
		cur_token = temp_token;
	}
}

void	ft_free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
	{
		free(path[i]);
		i++;
	}
	free(path);
}
