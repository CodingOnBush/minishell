/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:43:18 by momrane           #+#    #+#             */
/*   Updated: 2024/03/23 17:35:57 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_token	*ft_create_new_token(char *new_str)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->str = new_str;
	new_token->type = ft_get_type(new_str);
	new_token->attributed = false;
	new_token->next = NULL;
	return (new_token);
}

static void	ft_addlast_token(t_token **token_list, t_token *new_token)
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

int	ft_get_word_len(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (ft_is_quote(line[i]) && ft_strchr(&line[i + 1], line[i]) != NULL)
			i += ft_strchr(&line[i + 1], line[i]) - line + 1;
		else if (ft_is_quote(line[i]) && ft_strchr(&line[i + 1], line[i]) == NULL)
			return (FAIL);
		if (ft_is_in_word(line[i]) == NO)
			break;
		i++;
	}
	return (i);
}

char	*ft_get_new_str(char *line, int type)
{
	char	*new_str;
	int		len;

	if (type == PIPE || type == RIGHT_TRUNC || type == LEFT_TRUNC)
		len = 1;
	else if (type == HERE_DOC || type == APPEND)
		len = 2;
	else if (type == WORD || type == QWORD)
	{
		len = ft_get_word_len(line);
		if (len == FAIL)
			return (NULL);
	}
	else
		return (NULL);
	new_str = ft_strndup(line, len);
	if (!new_str)
		return (NULL);
	return (new_str);
}

static int	ft_add_new_token(t_token **token_list, char *line)
{
	t_token	*new_token;
	char	*new_str;

	new_str = ft_get_new_str(line, ft_get_type(line));
	if (!new_str)
		return (FAIL);
	new_token = ft_create_new_token(new_str);
	if (!new_token)
		return (free(new_str), FAIL);
	ft_addlast_token(token_list, new_token);
	return (SUCCESS);
}

t_token	*ft_create_token_list(char *line)
{
	t_token	*token_list;

	token_list = NULL;
	while (*line != '\0')
	{
		if (ft_isspace(*line) == YES)
			line++;
		else
		{
			if (ft_add_new_token(&token_list, line) == FAIL)
				return (ft_free_tokens(&token_list), NULL);
			line += ft_strlen(ft_findlast(token_list)->str);
		}
	}
	return (token_list);
}
