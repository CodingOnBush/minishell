/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 17:01:42 by momrane           #+#    #+#             */
/*   Updated: 2024/03/12 15:43:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void	ft_copy_chars(char *d, const char *s, size_t len)
{
	while (len-- && *s)
		*d++ = *s++;
	*d = '\0';
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*res;
	size_t	slen;

	if (!s)
		return (NULL);
	slen = ft_strlen(s);
	if (start >= slen)
	{
		res = ft_calloc(1, sizeof(char));
		if (!res)
			return (NULL);
		res[0] = '\0';
		return (res);
	}
	if (len > slen - start)
		len = slen - start;
	res = ft_calloc((len + 1), sizeof(char));
	if (!res)
		return (NULL);
	ft_copy_chars(res, s + start, len);
	return (res);
}

// #include <stdio.h>

// int	main(void)
// {
//     const char *s;
//     char *res;

// 	s = "Hello, World!";
// 	res = ft_substr(s, 7, 2);
//     if (res)
// 	{
//         printf("s: %s\n", s);
//         printf("res : %s\n", res);
//         free(res);
//     }
// 	else
//         printf("res is NULL\n");

//     return (0);
// }