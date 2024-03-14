/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:29:20 by momrane           #+#    #+#             */
/*   Updated: 2024/03/14 14:29:02 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_isspace(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (YES);
	return (NO);
}

int	ft_isappend(char *str)
{
	if (str[0] == '>' && str[1] == '>')
		return (YES);
	return (NO);
}

int	ft_isheredoc(char *str)
{
	if (str[0] == '<' && str[1] == '<')
		return (YES);
	return (NO);
}

int	ft_isoperator(char *str)
{
	if (ft_isappend(str) || ft_isheredoc(str))
		return (2);
	if (ft_strchr("|><", *str) != NULL)
		return (1);
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
	res = (char *)malloc(sizeof(char) * (n + 1));
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
		printf("type : %d\n", cur_token->type);
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
