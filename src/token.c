/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 11:43:18 by momrane           #+#    #+#             */
/*   Updated: 2024/03/14 11:43:44 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*ft_create_token(char *value, char *type)
{
	t_token	*new_token;

	new_token = malloc(sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	new_token->next = NULL;
	return (new_token);
}

void	ft_add_token(t_token **token_list, char *value)
{
	t_token	*cur_token;
	t_token	*new_token;

	if (value == NULL)
		return ;
	if (ft_isoperator(value))
		new_token = ft_create_token(value, "operator");
	else
		new_token = ft_create_token(value, "wip");
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
	if (c == DOUBLE_QUTOES || c == SINGLE_QUOTE)
	{
		line++;
		if (ft_strchr(line, c) == NULL)
			return (FAIL);
		step = ft_strchr(line, c) - line;// is 0 if "" or '' and is 6 if "coucou" or 'coucou'
		printf("step = %d\n", step);
		new_value = ft_strndup(line, step);
		if (!new_value)
			return (FAIL);
		ft_add_token(token_list, new_value);
		return (step + 2);
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
	return (token_list);
}


