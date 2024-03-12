/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 08:31:43 by momrane           #+#    #+#             */
/*   Updated: 2024/03/12 15:43:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_isinset(char c, char const *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static int	ft_getstart(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i] && ft_isinset(s1[i], set))
		i++;
	return (i);
}

static int	ft_getend(char const *s1, char const *set)
{
	int	i;

	i = ft_strlen(s1) - 1;
	while (i > 0 && ft_isinset(s1[i], set))
		i--;
	return (i);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*res;
	int		len1;
	int		len2;
	int		i;

	if (!s1 || !set)
		return (NULL);
	len1 = ft_getstart(s1, set);
	len2 = ft_getend(s1, set);
	if (len2 == 0)
		res = (char *)malloc(1 * sizeof(char));
	else
		res = (char *)malloc((len2 - len1 + 2) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (len1 <= len2)
	{
		res[i] = s1[len1];
		i++;
		len1++;
	}
	res[i] = '\0';
	return (res);
}

// #include <stdio.h>

// int main(void)
// {
// 	const char *s1 = "|||_--|||_--Hello, World!|||_---";
// 	const char *set = "|_-";
// 	char *result = ft_strtrim(s1, set);
// 
// 	printf("s1: %s\nRésultat après trim : \"%s\"\n", s1, result);
// 	free(result);
// 	return 0;
// }