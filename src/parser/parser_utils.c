/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:32:29 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 12:32:30 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_free_tokens_and_str(t_token *token, char *str)
{
	if (str)
		free(str);
	if (token)
		ft_free_tokens(&token);
}

t_token	*ft_extract_token(t_token *cur)
{
	t_token	*res;
	t_token	*new;
	char	*str;

	res = NULL;
	while (cur != NULL && cur->type != PIPE)
	{
		str = NULL;
		if (cur->value != NULL)
		{
			str = ft_strdup(cur->value);
			if (!str)
				return (ft_free_tokens(&res), NULL);
		}
		new = ft_new_token(str, cur->type, cur->pos, cur->to_expand);
		if (!new)
			return (ft_free_tokens_and_str(res, str), NULL);
		new->err_type = cur->err_type;
		new->error = cur->error;
		ft_addlast_token(&res, new);
		cur = cur->next;
	}
	return (res);
}

static int	ft_count_args(t_arg *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

static void	ft_free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i] != NULL)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	if (array)
		free(array);
}

char	**ft_create_args_array(t_arg *arg_list)
{
	char	**array;
	int		i;

	i = ft_count_args(arg_list);
	if (i == 0)
		return (NULL);
	array = ft_calloc(i + 1, sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (arg_list)
	{
		array[i] = ft_strdup(arg_list->value);
		if (!array[i])
			return (ft_free_array(array), NULL);
		i++;
		arg_list = arg_list->next;
	}
	array[i] = NULL;
	return (array);
}
