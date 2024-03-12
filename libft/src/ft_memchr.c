/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 07:37:01 by momrane           #+#    #+#             */
/*   Updated: 2024/03/12 15:43:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr;
	unsigned char	val;

	ptr = (unsigned char *)s;
	val = (unsigned char)c;
	while (n--)
	{
		if (*ptr == val)
			return ((void *)ptr);
		ptr++;
	}
	return (NULL);
}

// #include <stdio.h>
// #include <string.h>
// 
// int main(void)
// {
// 	char s[] = "Hello, World!";
// 	char *res = ft_memchr(s, 'W', 1);
// 
// 	printf("res: %s\n", res);
// 	return (0);
// }