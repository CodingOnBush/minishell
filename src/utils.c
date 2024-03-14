/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:29:20 by momrane           #+#    #+#             */
/*   Updated: 2024/03/14 09:52:33 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (YES);
	return (NO);
}

int	ft_isoperator(char *str)
{
	// printf("str : %s\n", str);
	if (ft_strchr("|><", *str) != NULL)
	{
		// printf("|>< found !\n");
		return (1);
	}
	if (ft_strncmp(str, "<<", 2) == 1 || ft_strncmp(str, ">>", 2) == 1)
	{
		// printf("<< or >> found\n");
		return (2);
	}
	return (0);
}

char	*ft_strndup(const char *s, int n)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(s);
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (i < len && i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}
