/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:17:05 by momrane           #+#    #+#             */
/*   Updated: 2024/03/12 15:43:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!lst || !new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}

// #include <stdio.h>

// int	main(void) {
// 	t_list *list = ft_lstnew("1");
// 	ft_lstadd_back(&list, ft_lstnew("2"));
// 	ft_lstadd_back(&list, ft_lstnew("3"));

// 	t_list *l = list;
// 	while (l)
// 	{
// 		printf("%p : [%s|%p]\n", l, (char *)l->content, l->next);
// 		l = l->next;
// 	}
// 	return (0);
// }