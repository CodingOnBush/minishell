/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 10:06:11 by momrane           #+#    #+#             */
/*   Updated: 2024/03/12 15:43:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_get_mem_size(int n)
{
	int	i;

	if (n == 0)
		return (1);
	i = 0;
	if (n < 0)
	{
		i++;
		n = n * (-1);
	}
	while (n > 0)
	{
		i++;
		n = n / 10;
	}
	return (i);
}

static char	*ft_itoa_neg(int n)
{
	char	*res;
	int		s;

	if (n == INT_MIN)
	{
		n++;
		res = ft_itoa_neg(n);
		if (!res)
			return (NULL);
		res[ft_get_mem_size(n) - 1] = '8';
		return (res);
	}
	s = ft_get_mem_size(n);
	n = n * (-1);
	res = malloc((s +1) * sizeof(char));
	if (!res)
		return (NULL);
	res[s--] = '\0';
	while (s >= 0)
	{
		res[s--] = n - ((n / 10) * 10) + 48;
		n = n / 10;
	}
	return (res);
}

char	*ft_itoa(int n)
{
	char	*res;
	int		s;

	if (n < 0)
	{
		res = ft_itoa_neg(n);
		if (!res)
			return (NULL);
		res[0] = '-';
		return (res);
	}
	s = ft_get_mem_size(n);
	res = (char *)malloc((s + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[s--] = '\0';
	while (s >= 0)
	{
		res[s--] = n - ((n / 10) * 10) + 48;
		n = n / 10;
	}
	return (res);
}

// #include <stdio.h>
// 
// int main(void)
// {
// 	int n = -42;
// 	char *res = ft_itoa(n);
// 
// 	if (res)
// 		printf("res : %s\n", res);
// 	return (0);
// }