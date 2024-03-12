/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 14:47:32 by momrane           #+#    #+#             */
/*   Updated: 2024/03/12 15:43:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	char		*d;
	const char	*s;

	d = (char *)dest;
	s = (const char *)src;
	while (n--)
		*d++ = *s++;
	return (dest);
}

// #include <stdio.h>
// #include <string.h>

// int main(void)
// {
// 	char src[] = "ABCD";
// 	char dest[50];
// 	char *res;

// 	// res = memcpy(dest, src, 2);
// 	// printf("src : %s\n", src);
// 	// printf("res : %s\n", res);

// 	res = ft_memcpy(dest, src, 2);
// 	printf("src : %s\n", src);
// 	printf("res : %s\n", res);
// 	return (0);
// }