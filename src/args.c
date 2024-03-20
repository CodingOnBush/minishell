/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:19:30 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/20 11:31:46 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_arg	*create_new_arg(char *value)
{
	t_arg	*new;

	new = malloc(sizeof(t_arg));
	if (!new)
		return (NULL);
	new->value = value;
	new->next = NULL;
	return (new);
}

int	add_new_arg(t_arg *head, char *value)
{
	t_arg	*new;
	
	new = create_new_arg(value);
	if (!new)
		return (FAIL);
	if (!head)
		head = new;
	else
	{
		while (head->next)
			head = head->next;
		head->next = new;
	}
	return (SUCCESS);
}