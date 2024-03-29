/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 11:19:30 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/27 22:49:56 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_arg	*create_new_arg(char *value)
{
	t_arg	*new_arg;

	new_arg = malloc(sizeof(t_arg));
	if (!new_arg)
		return (NULL);
	new_arg->value = value;
	new_arg->next = NULL;
	return (new_arg);
}

void	add_new_arg(t_arg **head, t_arg *new_arg)
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

int	ft_get_arg_nbr(t_arg *arg_list)
{
	int	count;

	count = 0;
	while (arg_list)
	{
		count++;
		arg_list = arg_list->next;
	}
	return (count);
}

char	**ft_arg_list_to_array(t_arg *arg_list)
{
	char	**array;
	int		len;
	int		i;

	if (!arg_list)
		return (NULL);
	len = ft_get_arg_nbr(arg_list);
	array = malloc((len + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (i < len)
	{
		array[i] = ft_strdup(arg_list->value);
		i++;
		arg_list = arg_list->next;
	}
	array[i] = NULL;
	return (array);
}
