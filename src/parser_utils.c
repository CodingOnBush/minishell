/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:39:05 by allblue           #+#    #+#             */
/*   Updated: 2024/04/21 18:54:29 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*ft_extract_token(t_token *cur_token)
{
	t_token	*res;
	t_token	*new;
	char	*str;

	res = NULL;
	while (cur_token != NULL && cur_token->type != PIPE)
	{
		if (cur_token->value == NULL)
			str = NULL;
		else
		{
			str = ft_strdup(cur_token->value);
			if (!str)
				return (ft_free_tokens(&res), NULL);
		}
		new = ft_new_token(str, cur_token->type, cur_token->pos, cur_token->error);
		if (!new)
			return (free(str), ft_free_tokens(&res), NULL);
		ft_addlast_token(&res, new);
		cur_token = cur_token->next;
	}
	return (res);
}

static int	ft_count_args(t_arg *lst)
{
	int		count;

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

	i = 0;
	while (array[i] != NULL)
	{
		if (array[i])
			free(array[i]);
		i++;
	}
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
