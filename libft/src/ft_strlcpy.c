/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 13:17:25 by momrane           #+#    #+#             */
/*   Updated: 2024/03/12 15:43:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	s;
	size_t	i;

	if (size == 0)
		return (ft_strlen(src));
	s = 0;
	i = 0;
	while (src[s] != '\0')
		s++;
	while ((src[i] != '\0') && (i < size - 1))
	{
		dst[i] = src[i];
		i++;
	}
	if (size > 0)
		dst[i] = '\0';
	return (s);
}

// #include <stdio.h>
// #include <bsd/string.h>

// int	main(void)
// {
// 	char src[] = "Hello, World!";
// 	char dst[20];
// 	size_t len = ft_strlcpy(dst, src, 20);

// 	printf("Source: %s\n", src);
// 	printf("Destination: %s\n", dst);
// 	printf("Length: %zu\n", len);

// 	return (0);
// }