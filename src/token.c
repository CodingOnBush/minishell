/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:43:18 by momrane           #+#    #+#             */
/*   Updated: 2024/03/27 16:19:40 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*ft_create_new_token(char *new_str, int type, int pos)
{
	t_token	*new_token;

	new_token = (t_token *)malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->str = new_str;
	new_token->type = type;
	new_token->attributed = false;
	new_token->pos = pos;
	new_token->error = false;
	new_token->err_type = -1;
	new_token->next = NULL;
	return (new_token);
}

void	ft_addlast_token(t_token **token_list, t_token *new_token)
{
	t_token	*lst;

	if (!new_token)
		return ;
	if (*token_list == NULL)
		*token_list = new_token;
	else
	{
		lst = *token_list;
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = new_token;
	}
}

static int	ft_get_token_size(char *line)
{
	int	type;
	int len;

	if (!line)
		return (FAIL);
	type = ft_get_type(line);
	if (type == PIPE || type == RIGHT_TRUNC || type == LEFT_TRUNC)
		return (1);
	if (type == HERE_DOC || type == APPEND)
		return (2);
	len = 0;
	while (line[len] && !ft_isspace(line[len]) && !ft_isop(&line[len]))
	{
		if (ft_isquote(line[len]))
			len += ft_strchr(&line[len + 1], line[len]) - line + 1;
		else
			len++;
	}
	return (len);
}

static char	*ft_extract_token_str(char *line)
{
	char	*str;
	int		len;

	len = ft_get_token_size(line);
	if (len == FAIL)
		return (NULL);
	str = ft_strndup(line, len);
	if (!str)
		return (NULL);
	return (str);
}

t_token	*ft_create_token_list(char *line)
{
	t_token	*token_list;
	t_token	*new_token;
	char	*new_str;
	int		pos;

	pos = 0;
	token_list = NULL;
	while (*line != '\0')
	{
		if (ft_isspace(*line) == YES)
			line++;
		else
		{
			new_str = ft_extract_token_str(line);
			if (!new_str)
				return (ft_free_tokens(&token_list), NULL);
			new_token = ft_create_new_token(new_str, ft_get_type(new_str), pos);
			if (!new_token)
				return (free(new_str), ft_free_tokens(&token_list), NULL);
			ft_addlast_token(&token_list, new_token);
			line += ft_strlen(new_str);
			pos++;
		}
	}
	return (token_list);
}
