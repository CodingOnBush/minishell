/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:17:12 by momrane           #+#    #+#             */
/*   Updated: 2024/03/12 15:43:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!new || !lst)
		return ;
	new->next = *lst;
	*lst = new;
}

// #include <stdio.h>

// int	main(void) {
// 	t_list *list = ft_lstnew("5");
// 	ft_lstadd_front(&list, ft_lstnew("4"));
// 	ft_lstadd_front(&list, ft_lstnew("3"));
// 	ft_lstadd_front(&list, ft_lstnew("2"));
// 	ft_lstadd_front(&list, ft_lstnew("1"));

// 	t_list *l = list;
// 	while (l)
// 	{
// 		printf("%p : [%s|%p]\n", l, (char *)l->content, l->next);
// 		l = l->next;
// 	}
// 	return (0);
// }