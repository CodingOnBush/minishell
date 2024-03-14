/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:03 by momrane           #+#    #+#             */
/*   Updated: 2024/03/14 10:41:05 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		printf("next-> %p\n", cur_token->next);
		printf("\n");
		cur_token = cur_token->next;
	}
}

t_token	*ft_findlast(t_token *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next != NULL)
		lst = lst->next;
	return (lst);
}

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
	char	*dup;
	char	c;

	step = -1;
	c = *line;
	line++;
	dup = NULL;
	printf("c = %c\n", c);
	if (c == DOUBLE_QUTOES || c == SINGLE_QUOTE)
	{
		if (ft_strchr(line, c) == NULL)
			return (-1);
		step = ft_strchr(line, c) - line;// is 0 if "" or '' and is 6 if "coucou" or 'coucou'
		if (step > 0)
		{
			dup = ft_strndup(line, step);
			if (dup == NULL)
				return (-1);
		}
		step += 2;// +2 to skip the two single quotes or double quotes
	}
	else if (c == '|' || c == '<' || c == '>')
	{
		step = 1;
		if (*line == '<' || *line == '>')
			step = 2;
		dup = ft_strndup(line, step);
		if (dup == NULL)
			return (-1);
	}
	else
	{
		step = 0;
		while (line[step] != '\0' && !ft_isspace(line[step]) && !ft_isoperator(&line[step]))
			step++;
		dup = ft_strndup(line, step);
		if (dup == NULL)
			return (-1);
	}
	ft_add_token(token_list, dup);
	return (step);
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
			if (step < 0)
				return (ft_free_tokens(&token_list), NULL);
			line += step;
		}
	}
	return (token_list);
}

int	main(int ac, char **av)
{
	t_data	data;

	(void)ac;
	// printf("Welcome to minispell \\o_o/\n");
	// while (1)
	// {
		// data.line = readline("minispell > ");
		// if (!data.line)
			// break ;
		data.line = av[1];//"hey | \"coucou\" | hey |";
		// printf("%s\n", data.line);
		
		data.token_list = ft_create_token_list(data.line);
		if (data.token_list)
			print_list(data.token_list);
		else
			printf("no token list\n");
		// free(data.line);
	// }
	return (0);
}
