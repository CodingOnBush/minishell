/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:03 by momrane           #+#    #+#             */
/*   Updated: 2024/03/13 16:18:01 by momrane          ###   ########.fr       */
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
	int		word_len;
	char	*scd_double_quote;
	char	*tmp;

	i = 0;
	token_list = NULL;
	while (line[i] != '\0')
	{
		if (ft_isspace(line[i]) == YES)
		{
			// printf("space found\n");
			i++;
		}
		else
		{
			if (line[i] == DQ)
			{
				// printf("coucouc\n");
				scd_double_quote = ft_strchr(&line[i + 1], DQ);
				if (scd_double_quote != NULL)
				{
					word_len = scd_double_quote - &line[i] - 1;
					tmp = ft_strndup(&line[i + 1], word_len);
					// printf("word_len = %d\n", word_len);
					// return (token_list);
					ft_add_token(&token_list, tmp);
					i += word_len + 2;
				}
				else
					return (ft_free_tokens(&token_list), NULL);
			}
			else if (ft_isoperator(&line[i]) != 0)
			{
				if (ft_isoperator(&line[i]) == 1)
					tmp = ft_strndup(&line[i], 1);
				else if (ft_isoperator(&line[i]) == 2)
					tmp = ft_strndup(&line[i], 2);
				// printf("tmp = %s\n", tmp);
				ft_add_token(&token_list, tmp);
				// printf("i before = %d\n", i);
				i += ft_isoperator(&line[i]);
				// printf("i after = %d\n", i);
				// print_list(token_list);
			}
			else
				i++;
		}
	}
	return (token_list);
}

int	main(void)
{
	t_data	data;

	printf("Welcome to minispell \\o_o/\n");
	// while (1)
	// {
		// data.line = readline("minispell > ");
		// if (!data.line)
			// break ;
		data.line = "hey | \"coucou\" | hey";
		printf("%s\n", data.line);
		
		data.token_list = ft_create_token_list(data.line);
		if (data.token_list)
			print_list(data.token_list);
		else
			printf("no token list\n");
		// free(data.line);
	// }
	return (0);
}
