/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 13:48:23 by momrane           #+#    #+#             */
/*   Updated: 2024/03/12 15:43:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_bzero(void *s, size_t n)
{
	char	*ptr;

	ptr = (char *)s;
	while (n--)
	{
		*ptr = '\0';
		ptr++;
	}
}

// #include <stdio.h>
// #include <strings.h>

// int	main(void) {
// 	char s[5] = "01234";

// 	printf("s[0] : %d\n", s[0]);
// 	printf("s[1] : %d\n", s[1]);
// 	printf("s[2] : %d\n", s[2]);
// 	printf("s[3] : %d\n", s[3]);
// 	printf("s[4] : %d\n", s[4]);
// 	ft_bzero(s, 5);
// 	// bzero(s, 5);
// 	printf("s[0] : %d\n", s[0]);
// 	printf("s[1] : %d\n", s[1]);
// 	printf("s[2] : %d\n", s[2]);
// 	printf("s[3] : %d\n", s[3]);
// 	printf("s[4] : %d\n", s[4]);
// 	return (0);
// }