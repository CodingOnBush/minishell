/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:29:20 by momrane           #+#    #+#             */
/*   Updated: 2024/03/22 15:20:35 by momrane          ###   ########.fr       */
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

int	ft_isredirection(char *str)
{
	if (ft_isappend(str))
		return (2);
	if (ft_strchr("><", *str) != NULL)
		return (1);
	return (0);
}

int	ft_isoperator(char *str)
{
	if (ft_isappend(str) || ft_isheredoc(str))
		return (2);
	if (ft_strchr("|><", *str) != NULL)
		return (1);
	return (FAIL);
}

int	ft_is_in_word(char c)
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
		printf("str : %s\n", cur_token->str);
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

void	ft_set_path(t_data *data)
{
	int		i;
	char	*path;
	char	**tmp;

	i = 0;
	while (data->env[i])
	{
		if (ft_strncmp(data->env[i], "PATH=", 5) == 0)
		{
			path = ft_strdup(data->env[i] + 5);
			tmp = ft_split(path, ':');
			free(path);
			data->path = tmp;
			return ;
		}
		i++;
	}
	data->path = NULL;
}

int	ft_get_op_type(char *value)
{
	if (value[0] == '|')
		return (PIPE);
	if (ft_isheredoc(value) == YES)
		return (HERE_DOC);
	if (ft_isappend(value) == YES)
		return (APPEND);
	if (value[0] == '<')
		return (LEFT_TRUNC);
	if (value[0] == '>')
		return (RIGHT_TRUNC);
	return (FAIL);
}

int	ft_get_type(char *str)
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
	if (*str == DOUBLE_QUOTES || *str == SINGLE_QUOTE)
		return (QWORD);
	return (WORD);
}

char	*ft_type_to_str(int type)
{
	if (type == PIPE)
		return ("PIPE");
	if (type == HERE_DOC)
		return ("HERE_DOC");
	if (type == APPEND)
		return ("APPEND");
	if (type == LEFT_TRUNC)
		return ("LEFT_TRUNC");
	if (type == RIGHT_TRUNC)
		return ("RIGHT_TRUNC");
	if (type == WORD)
		return ("WORD");
	if (type == NEWLINE_ERROR)
		return ("NEWLINE_ERROR");
	if (type == QUOTES_ERROR)
		return ("QUOTES_ERROR");
	if (type == SINGLE_QUOTE_ERROR)
		return ("SINGLE_QUOTE_ERROR");
	if (type == DOUBLE_QUOTE_ERROR)
		return ("DOUBLE_QUOTE_ERROR");
	if (type == QWORD)
		return ("QWORD");
	return ("UNKNOWN");
}
