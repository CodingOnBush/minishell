/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 07:06:13 by momrane           #+#    #+#             */
/*   Updated: 2024/03/12 15:43:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*ptr;
	char			*res;
	unsigned char	val;

	ptr = (char *)s;
	res = NULL;
	val = (unsigned char)c;
	while (*ptr != '\0')
	{
		if (*ptr == val)
			res = ptr;
		ptr++;
	}
	if (res != NULL)
		return (res);
	if (*ptr == val)
		res = ptr;
	return (res);
}

// #include <stdio.h>

// int main(void)
// {
// 	const char *str = "Hello, World!";
// 	int ch = 'o';
// 	char *result = ft_strrchr(str, ch);

// 	if (result != NULL) {
// 		printf("'%c' trouvé à la pos : %ld\n", ch, result - str);
// 	} else {
// 		printf("'%c' pas trouvé...\n", ch);
// 	}

// 	return (0);
// }
