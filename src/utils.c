/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:29:20 by momrane           #+#    #+#             */
/*   Updated: 2024/03/14 11:43:22 by momrane          ###   ########.fr       */
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
	if (ft_strchr("|><", *str) != NULL)
		return (1);
	if (ft_strncmp(str, "<<", 2) == 1 || ft_strncmp(str, ">>", 2) == 1)
		return (2);
	return (0);
}

int	ft_isword(char c)
{
	if (c != '|' && c != '>' && c != '<' && ft_isspace(c) == NO)
		return (YES);
	return (NO);
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

void	print_list(t_token *list)
{
	t_token	*cur_token;

	if (list == NULL)
	{
		printf("empty list");
		return ;
	}
	cur_token = list;
	while (cur_token != NULL)
	{
		printf("address: %p\n", cur_token);
		printf("value : %s\n", cur_token->value);
		printf("type : %s\n", cur_token->type);
		printf("next-> %p\n", cur_token->next);
		printf("\n");
		cur_token = cur_token->next;
	}
}

t_token		*ft_findlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}
