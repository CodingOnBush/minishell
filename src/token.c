/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:43:18 by momrane           #+#    #+#             */
/*   Updated: 2024/03/21 12:42:14 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

t_token	*ft_create_token(char *value)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	if (ft_isoperator(value))
	{
		new_token->type = ft_get_op_type(value);
		if (new_token->type == FAIL)
			return (NULL);
	}
	else
		new_token->type = WORD;
	new_token->next = NULL;
	return (new_token);
}

void	ft_add_token(t_token **token_list, char *value)
{
	t_token	*cur_token;
	t_token	*new_token;

	if (value == NULL)
		return ;
	new_token = ft_create_token(value);
	if (!new_token)
		return ;
	cur_token = ft_findlast(*token_list);
	if (cur_token == NULL)
		*token_list = new_token;
	else
		cur_token->next = new_token;
}

int	ft_add_new_token(t_token **token_list, char *line)
{
	int		step;
	char	*new_value;
	char	c;

	step = -1;
	c = *line;
	new_value = NULL;
	printf("c = %c\n", c);
	if (c == DOUBLE_QUOTES || c == SINGLE_QUOTE)
	{
		if (ft_strchr(line + 1, c) == NULL)
		{
			ft_putstr_fd("Unclosed single or double quote\n", 2);
			return (FAIL);
		}
		step = ft_strchr(line + 1, c) - line + 1;
		printf("step = %d\n", step);
		new_value = ft_strndup(line, step);
		if (!new_value)
			return (FAIL);
		ft_add_token(token_list, new_value);
		return (step);
	}
	else if (ft_isword(c) == YES)
	{
		step = 0;
		while (line[step] != '\0' && ft_isword(line[step]))
			step++;
		new_value = ft_strndup(line, step);
		if (!new_value)
			return (FAIL);
		ft_add_token(token_list, new_value);
		return (step);
	}
	else
	{
		step = ft_isoperator(line);
		if (step == 0)
			return (FAIL);
		printf("step : %d\n", step);
		new_value = ft_strndup(line, step);
		if (!new_value)
			return (FAIL);
		ft_add_token(token_list, new_value);
		return (step);
	}
	return (FAIL);
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
			step = ft_add_new_token(&token_list, line);
			if (step == FAIL)
				return (ft_free_tokens(&token_list), NULL);
			line += step;
		}
	}
	if (check_token_list(token_list) == FAIL)
		token_list = NULL;
	return (token_list);
}
