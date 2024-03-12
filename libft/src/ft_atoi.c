/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 12:34:16 by momrane           #+#    #+#             */
/*   Updated: 2024/03/12 15:43:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_issign(char c)
{
	if (c == '+' || c == '-')
		return (1);
	return (0);
}

static int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int	i;
	int	sign;
	int	res;

	i = 0;
	sign = 1;
	res = 0;
	while (nptr[i] && ft_isspace(nptr[i]))
		i++;
	if (ft_issign(nptr[i]))
	{
		if (nptr[i] == '-')
			sign = sign * (-1);
		i++;
	}
	while (ft_isdigit(nptr[i]) && nptr[i])
		res = (res * 10) + (nptr[i++] - 48);
	return (sign * res);
}

// #include <stdio.h>

// int	main(void)
// {
// 	const char *s = "-42";

// 	printf("atoi(%s) : %d\n", s, atoi(s));
// 	printf("ft_atoi(%s): %d\n", s, ft_atoi(s));
// 	return (0);
// }
