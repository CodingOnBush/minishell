/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 14:17:41 by momrane           #+#    #+#             */
/*   Updated: 2024/03/12 15:43:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_element;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_element = ft_lstnew(f(lst->content));
		if (!new_element)
		{
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_element);
		lst = lst->next;
	}
	return (new_list);
}

// #include <stdio.h>
// #include <string.h>
// #include <ctype.h>

// void *transform_content(void *content)
// {
//     // Check if the content pointer is valid
//     if (content == NULL) {
//         return NULL;
// }
//     char *str = (char *)content;
//     char *result = strdup(str); // Duplicate the original content
//     // Convert each character in the duplicated string to uppercase
//     for (size_t i = 0; result[i]; i++) {
//         result[i] = toupper(result[i]);
//     }
//     return result;
// }

// void free_content(void *content)
// {
//     free(content);
// }

// void print(void *content)
// {
// 	printf("content : %s\n", (char *)content);
// }

// int	main(void)
// {
// 	t_list *lst = ft_lstnew("hello");
// 	ft_lstadd_back(&lst, ft_lstnew("world"));

// 	printf("lst\n");
// 	ft_lstiter(lst, &print);
//
// 	printf("new_lst\n");
// 	t_list *new_lst = ft_lstmap(lst, &transform_content, &free_content);
// 	ft_lstiter(new_lst, &print);

// 	return (0);
// }
