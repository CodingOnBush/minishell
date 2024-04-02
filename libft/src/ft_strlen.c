/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:31:17 by momrane           #+#    #+#             */
/*   Updated: 2024/04/02 17:37:20 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlen(const char *s)
{
	int		i;
	char	*str;
	size_t	res;

	if (s == NULL)
		return (0);
	str = (char *)s;
	i = 0;
	while (str[i] != '\0')
		i++;
	res = (size_t)i;
	return (res);
}
