/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 14:18:27 by momrane           #+#    #+#             */
/*   Updated: 2024/03/12 15:43:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*res;

	if (nmemb == 0 || size == 0)
		res = malloc(1);
	else if (nmemb > SIZE_MAX / size)
		return (NULL);
	else
		res = malloc(nmemb * size);
	if (!res)
		return (NULL);
	ft_bzero(res, nmemb * size);
	return (res);
}

// #include <stdio.h>
// #include <stdlib.h>

// int	main(void) {
// 	size_t nmemb = 10;
// 	int	i = 0;
// 	int *s = (int *)calloc(nmemb, sizeof(int));

// 	if (!s)
// 		return (0);
// 	while (i <= nmemb)
// 	{
// 		printf("s[%d] : %d\n", i, s[i]);
// 		i++;
// 	}
// 	free(s);
// 	return (0);
// }