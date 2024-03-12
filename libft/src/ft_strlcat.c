/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:33:02 by momrane           #+#    #+#             */
/*   Updated: 2024/03/12 15:43:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dlen;
	size_t	slen;
	size_t	result;

	dlen = ft_strlen(dest);
	slen = ft_strlen(src);
	if (size <= dlen)
		result = size + slen;
	else
	{
		result = dlen + slen;
		while (*src && dlen < size - 1)
		{
			dest[dlen] = *src;
			dlen++;
			src++;
		}
		dest[dlen] = '\0';
	}
	return (result);
}

// #include <stdio.h>
// #include <bsd/string.h>

// int main(void)
// {
// 	char *dest;
// 	const char src[] = " World";
// 	size_t size = 3;

// 	dest = "Hello";
// 	size_t result1 = ft_strlcat(dest, src, size);
// 	printf("Result: %s, Length: %zu\n", dest, result1);

// 	// dest = "Hello";
// 	// size_t result2 = strlcat(dest, src, size);
// 	// printf("Result: %s, Length: %zu\n", dest, result2);
// 	return (0);
// }