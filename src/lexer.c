/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 14:47:50 by momrane           #+#    #+#             */
/*   Updated: 2024/04/07 17:53:38 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_print_token_list(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	printf("TOKEN LIST\n");
	if (!tmp)
		printf("nil");
	while (tmp)
	{
		printf("%s\t\t%s\t\t%d\t%d\t%d\t%s\n", tmp->str, ft_type_to_str(tmp->type), tmp->attributed, tmp->pos, tmp->error, ft_type_to_str(tmp->err_type));
		tmp = tmp->next;
	}
}

int	ft_lexer(t_data *data)
{
	if (ft_check_quote_error(data->line) == NO)
		return (ft_print_error(QUOTES_ERROR), FAIL);
	data->token_list = ft_create_token_list(data->line);
	if (!data->token_list)
		return (FAIL);
	ft_set_delimiters(&data->token_list);
	ft_expand_words(&data->token_list);
	if (check_token_list(data->token_list) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
