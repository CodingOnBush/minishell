/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:31:01 by momrane           #+#    #+#             */
/*   Updated: 2024/03/12 15:43:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static void	ft_fillstr(char *res, const char *s, int *r)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		res[*r] = s[i];
		(*r)++;
		i++;
	}
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len1;
	int		len2;
	char	*res;
	int		r;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	res = malloc((len1 + len2 + 1) * sizeof(char));
	if (!res)
		return (NULL);
	r = 0;
	ft_fillstr(res, s1, &r);
	ft_fillstr(res, s2, &r);
	res[r] = '\0';
	return (res);
}

// #include <stdio.h>

// int	main(void)
// {
// 	char *s1 = "Hello, ";
// 	char *s2 = "World!";
// 	char *result = ft_strjoin(s1, s2);

// 	if (!result)
// 		return (0);
// 	printf("Résultat de la concaténation : %s\n", result);
// 	free(result);
// 	return (0);
// }