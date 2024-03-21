/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:43:18 by momrane           #+#    #+#             */
/*   Updated: 2024/03/21 17:22:52 by momrane          ###   ########.fr       */
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

static char	*ft_get_new_str(char *line, int type)
{
	char	*new_str;
	int		len;

	if (type == PIPE || type == RTRUNC || type == LTRUNC)
		len = 1;
	else if (type == HEREDOC || type == APPEND)
		len = 2;
	else if (type == QWORD)
	{
		if (ft_strchr(line + 1, *line) == NULL)
			return (ft_error_messages(QUOTES_ERROR), NULL);
		len = ft_strchr(line + 1, *line) - line + 1;
	}
	else if (type == WORD)
	{
		len = 0;
		while (line[len] != '\0' && ft_is_in_word(line[len]) == YES)
			len++;
	}
	else
		return (NULL);
	new_str = ft_strndup(line, len);
	if (!new_str)
		return (NULL);
	return (new_str);
}

static int	ft_handle_token(t_token **token_list, char *line)
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
	return (ft_strlen(new_str));
}

t_token	*ft_create_token_list(char *line)
{
	t_token	*token_list;
	int		step;

	token_list = NULL;
	while (*line != '\0')
	{
		if (ft_isspace(*line) == YES)
			line++;
		else
		{
			step = ft_handle_token(&token_list, line);
			if (step == FAIL)
				return (NULL);
			line += step;
		}
	}
	if (check_token_list(token_list) == FAIL)
		return (ft_free_tokens(&token_list), NULL);
	return (token_list);
}
