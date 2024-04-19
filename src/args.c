/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:19:30 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/19 15:32:54 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_arg	*ft_new_arg(char *value, int token_type)
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

void	ft_add_new_arg(t_arg **head, t_arg *new_arg)
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

