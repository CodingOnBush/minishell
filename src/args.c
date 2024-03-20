/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:19:30 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/20 13:49:42 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_arg	*create_new_arg(char *value)
{
	t_arg	*new_arg;

	new_arg = malloc(sizeof(t_arg));
	if (!new_arg)
		return (NULL);
	new_arg->value = value;
	new_arg->next = NULL;
	return (new_arg);
}

int	add_new_arg(t_arg **head, char *value)
{
	t_arg	*new_arg;

	new_arg = create_new_arg(value);
	if (new_arg == NULL)
		return (FAIL);
	if (*head == NULL)
		*head = new_arg;
	else
	{
		while ((*head)->next != NULL)
			*head = (*head)->next;
		(*head)->next = new_arg;
	}
	return (SUCCESS);
}
