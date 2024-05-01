/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:19:30 by vvaudain          #+#    #+#             */
/*   Updated: 2024/05/01 10:23:27 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_arg	*ft_new_arg(char *value, int token_type)
{
	t_arg	*new_arg;

	new_arg = malloc(sizeof(t_arg));
	if (!new_arg)
		return (NULL);
	new_arg->value = value;
	new_arg->token_type = token_type;
	new_arg->next = NULL;
	return (new_arg);
}

static void	ft_add_new_arg(t_arg **head, t_arg *new_arg)
{
	t_arg	*arg_list;

	if (*head == NULL)
		*head = new_arg;
	else
	{
		arg_list = *head;
		while (arg_list->next != NULL)
			arg_list = arg_list->next;
		arg_list->next = new_arg;
	}
}

t_arg	*ft_create_arg_list(t_token *token)
{
	t_arg	*new;
	t_arg	*res;

	res = NULL;
	while (token != NULL && token->type != PIPE)
	{
		if (token->attributed == false && ft_isop(token->value)
			&& *token->value == '\0')
		{
			new = ft_new_arg(ft_strdup(token->value), token->type);
			if (!new)
				return (ft_free_arg_list(&res), NULL);
			ft_add_new_arg(&res, new);
		}
		else if ((token->attributed == false && ft_isop(token->value) == NO
				&& token->value != NULL))
		{
			new = ft_new_arg(ft_strdup(token->value), token->type);
			if (!new)
				return (ft_free_arg_list(&res), NULL);
			ft_add_new_arg(&res, new);
		}
		token = token->next;
	}
	return (res);
}

void	ft_free_arg_list(t_arg **arg_list)
{
	t_arg	*cur;
	t_arg	*next;

	cur = *arg_list;
	while (cur != NULL)
	{
		next = cur->next;
		if (cur->value)
			free(cur->value);
		free(cur);
		cur = next;
	}
	*arg_list = NULL;
}
