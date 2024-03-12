/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 16:09:37 by momrane           #+#    #+#             */
/*   Updated: 2024/03/12 15:43:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strdup(const char *s)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(s);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

// #include <stdio.h>

// int main() {
// 	const char *originalString = "Hello, this is a test string.";
// 	char *duplicateString = ft_strdup(originalString);

// 	if (duplicateString != NULL) {
// 		printf("Original: %s\n", originalString);
// 		printf("Duplicate: %s\n", duplicateString);
// 		free(duplicateString);
// 	} else {
// 		printf("duplicateString is NULL.\n");
// 	}

// 	return 0;
// }