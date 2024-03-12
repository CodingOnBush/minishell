/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 11:52:04 by momrane           #+#    #+#             */
/*   Updated: 2024/03/12 15:43:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*res;

	if (!s)
		return (NULL);
	res = (char *)malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s[i])
	{
		res[i] = f(i, s[i]);
		i++;
	}
	res[i] = '\0';
	return (res);
}

// char	func(unsigned int i, char c)
// {
// 	if (c >= 'A' && c <= 'Z')
// 		return (c + 32);
// 	else if (c >= 'a' && c <= 'z')
// 		return (c - 32);
// 	else
// 		return (c);
// }

// #include <stdio.h>

// int	main(void)
// {
// 	char	*res;
// 	char const	*s = "bonjour comment cava ?";
// 	res = ft_strmapi(s, &func);
// 	printf("res :%s\n", res);
// 	return (0);
// }