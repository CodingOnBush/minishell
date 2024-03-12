/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:38:31 by momrane           #+#    #+#             */
/*   Updated: 2024/03/12 15:43:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;

	if (!dest && !src)
		return (dest);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	if (d > s && d < s + n)
	{
		d += n;
		s += n;
		while (n--)
			*--d = *--s;
	}
	else
		ft_memcpy(d, s, n);
	return (dest);
}

// #include <stdio.h>
// #include <string.h>
// 
// int	main(void)
// {
// 	char	src[] = "ABCD";
// 	char	dest[40];
// 
// 	printf("src : %s\n", src);
// 	ft_memmove(src + 2, src, 0);
// 	printf("src : %s\n", src);
// 
// 	return (0);
// }