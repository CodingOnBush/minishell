/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:03 by momrane           #+#    #+#             */
/*   Updated: 2024/03/13 14:51:48 by vvaudain         ###   ########.fr       */
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

t_token	*ft_create_token_list(char *line)
{
	int		i;
	t_token	*token_list;

	i = 0;
	token_list = NULL;
	while (line[i] != '\0')
	{
		if (ft_isspace(line[i]) == YES)
			i++;
		else
		{
			if (line[i] == '|')
				ft_add_token(&token_list, "|");
			else if (line[i] == '>' && line[i + 1] == '>')
				ft_add_token(&token_list, ">>");
			else if (line[i] == '<' && line[i + 1] == '<')
				ft_add_token(&token_list, "<<");
			else if (line[i] == '>' && line[i + 1] != '>')
				ft_add_token(&token_list, ">");
			else if (line[i] == '<' && line[i + 1] != '<')
				ft_add_token(&token_list, "<");
			else
			{
				
			}
			i++;
		}
	}
	printf("%p\n", token_list);
	return (token_list);
}

int	main(void)
{
	t_data	data;

	printf("Welcome to minispell \\o_o/\n");
	while (1)
	{
		data.line = readline("minispell > ");
		if (!data.line)
			break ;
		printf("%s\n", data.line);
		
		data.token_list = ft_create_token_list(data.line);
		if (data.token_list)
			print_list(data.token_list);
		free(data.line);
	}
	return (0);
}
