/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:30:45 by momrane           #+#    #+#             */
/*   Updated: 2024/04/26 11:12:05 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_strndup(char *s, int n)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(s);
	if (len == 0)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (n + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_super_strjoin(char *new_str, char *toadd)
{
	int		new_str_len;
	int		toadd_len;
	int		new_len;
	char	*join;

	if (new_str == NULL && toadd == NULL)
		return (NULL);
	new_str_len = ft_strlen(new_str);
	toadd_len = ft_strlen(toadd);
	new_len = new_str_len + toadd_len;
	join = malloc(sizeof(char) * (new_len + 1));
	if (!join)
		return (NULL);
	if (new_str != NULL)
		ft_strlcpy(join, new_str, new_str_len + 1);
	if (toadd)
		ft_strlcpy(join + new_str_len, toadd, toadd_len + 1);
	join[new_len] = '\0';
	if (new_str != NULL)
		free(new_str);
	if (toadd != NULL)
		free(toadd);
	return (join);
}

int	ft_is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (YES);
	return (NO);
}

int	ft_isquote(char c)
{
	if (c == DOUBLE_QUOTES || c == SINGLE_QUOTE)
		return (YES);
	return (NO);
}

int	ft_is_in_var(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (YES);
	return (NO);
}
