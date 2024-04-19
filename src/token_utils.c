/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/02 16:41:05 by momrane           #+#    #+#             */
/*   Updated: 2024/04/19 16:56:47 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_set_delimiters(t_token **token_list)
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

t_token		*ft_findlast_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

void	ft_addlast_token(t_token **token_list, t_token *new_token)
{
	t_token	*lst;

	if (!new_token)
		return ;
	if (*token_list == NULL)
		*token_list = new_token;
	else
	{
		lst = *token_list;
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = new_token;
	}
}

t_token	*ft_extract_token(t_token *cur_token)
{
	t_token	*res;
	t_token	*new;
	char	*str;

	res = NULL;
	while (cur_token != NULL && cur_token->type != PIPE)
	{
		if (cur_token->str == NULL)
			str = NULL;
		else
		{
			str = ft_strdup(cur_token->str);
			if (!str)
				return (ft_free_tokens(&res), NULL);
		}
		new = ft_new_token(str, cur_token->type, cur_token->pos, cur_token->error);
		if (!new)
			return (free(str), ft_free_tokens(&res), NULL);
		ft_addlast_token(&res, new);
		cur_token = cur_token->next;
	}
	return (res);
}

