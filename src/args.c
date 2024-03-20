/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:19:30 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/20 12:51:11 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_word	*create_new_arg(char *value)
{
	t_word	*new_word;

	new_word = malloc(sizeof(t_word));
	if (!new_word)
		return (NULL);
	new_word->value = value;
	new_word->next = NULL;
	return (new_word);
}

int	add_new_word(t_word **head, char *value)
{
	t_word	*new_word;

	new_word = create_new_arg(value);
	if (new_word == NULL)
		return (FAIL);
	if (*head == NULL)
		*head = new_word;
	else
	{
		while ((*head)->next != NULL)
			*head = (*head)->next;
		(*head)->next = new_word;
	}
	return (SUCCESS);
}
