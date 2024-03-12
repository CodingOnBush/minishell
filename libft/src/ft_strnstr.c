/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:22:17 by momrane           #+#    #+#             */
/*   Updated: 2024/03/12 15:43:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if ((!big || !little) && len == 0)
		return ((char *)big);
	while (big[i] && little[j] && i < len)
	{
		if (little[j] == big[i])
			j++;
		else
		{
			i -= j;
			j = 0;
		}
		i++;
	}
	if (little[j] == '\0')
		return ((char *)&big[i - j]);
	return (NULL);
}

// #include <stdio.h>

// int	main(void)
// {
// 	const char *big = "Hello, World!";
// 	const char *little = "World";
// 	char *result = ft_strnstr(big, little, 13);

// 	if (result != NULL)
// 		printf("'%s' trouvée dans '%s' en %ld\n", little, big, result - big);
// 	else
// 		printf("'%s' pas trouvée dans '%s'\n", little, big);
// 	return (0);
// }