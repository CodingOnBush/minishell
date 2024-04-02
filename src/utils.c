/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:29:20 by momrane           #+#    #+#             */
/*   Updated: 2024/04/02 12:02:53 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_isspace(char c)
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

int	ft_isappend(char *str)
{
	if (!str)
		return (NO);
	if (str[0] == '>' && str[1] && str[1] == '>')
		return (YES);
	return (NO);
}

int	ft_isheredoc(char *str)
{
	if (!str)
		return (NO);
	if (str[0] == '<' && str[1] && str[1] == '<')
		return (YES);
	return (NO);
}

int	ft_isop(char *str)
{
	if (ft_isappend(str) || ft_isheredoc(str))
		return (YES);
	if (ft_strchr("><", *str) != NULL)
		return (YES);
	return (NO);
}

int  ft_get_type(char *str)
{
	if (*str == '|')
		return (PIPE);
	if (ft_isheredoc(str) == YES)
		return (HERE_DOC);
	if (ft_isappend(str) == YES)
		return (APPEND);
	if (*str == '<')
		return (LEFT_TRUNC);
	if (*str == '>')
		return (RIGHT_TRUNC);
	return (WORD);
}

char	*ft_strndup(char *s, int n)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(s);
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

int	ft_isoperator(char *str)
{
	if (ft_isappend(str) || ft_isheredoc(str))
		return (2);
	if (ft_strchr("|><", *str) != NULL)
		return (1);
	return (NO);
}

t_token		*ft_findlast_token(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

char	*ft_type_to_str(int type)
{
	if (type == PIPE)
		return ("PIPE");
	if (type == PIPE_AT_END)
		return ("PIPE_AT_END");
	if (type == HERE_DOC)
		return ("HEREDOC");
	if (type == APPEND)
		return ("APPEND");
	if (type == LEFT_TRUNC)
		return ("LTRUNC");
	if (type == RIGHT_TRUNC)
		return ("RTRUNC");
	if (type == WORD)
		return ("WORD");
	if (type == NEWLINE_ERROR)
		return ("ERRNEWLINE");
	if (type == QUOTES_ERROR)
		return ("ERRQUOTE");
	if (type == SINGLE_QUOTE_ERROR)
		return ("SINGLE_QUOTE_ERROR");
	if (type == DOUBLE_QUOTE_ERROR)
		return ("DOUBLE_QUOTE_ERROR");
	if (type == QWORD)
		return ("QWORD");
	return ("UNKNOWN");
}

int	ft_get_pipe_count(t_token *token_list)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = token_list;
	while (tmp)
	{
		if (tmp->type == PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

/* char	*ft_get_cmd_path(char *cmd)
{
	
} */


