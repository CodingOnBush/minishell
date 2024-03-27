/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:16:46 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/27 13:26:49 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	is_dollar(char *str)
{
	int	i;
	
	if (!str)
		return (NO);
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (YES);
		i++;
	}
	return (NO);
}

int	ft_check_expands(t_token *list)
{
	t_token	*cur_token;
	char	*tmp;

	if (!list)
		return ;
	cur_token = list;
	while (cur_token != NULL)
	{
		if (cur_token->type == WORD && is_dollar(cur_token->str) == YES)
		{
			tmp = cur_token->str;
			cur_token->str = ft_get_vars(tmp);
			if (cur_token->str == NULL)
				return (FAIL);
			free(tmp);
		}
		cur_token = cur_token->next;
	}
	return (SUCCESS);
}

//On veut recuperer la ligne VAR --> on peut utiliser strncmp avec strlen de notre nom de var


char	*ft_get_vars(char *str)
{
	int		i;
	char	*ret_value;
	char	*tmp;

	if (!str)
		return (NULL);
	i = 0;
	ret_value = NULL;
	tmp = NULL;
	while (*str)
	{
		i = 0;
		while (str[i] != '\'' && str[i] != '\"' && str[i] != '$')
			i++;
		if (i != 0 && str[i] != NULL)
		{
			ft_strlcpy(tmp, *str, i + 1); // voir si ok de mettre i + 1 et si pas i + 2
			ret_value = ft_strjoin(ret_value, tmp);
			free(tmp);
			str += i;
		}
		if (str[i] == '\'')
		{
			i = dist_to_quote(*str);
			ft_strlcpy(tmp, str, i);
			ret_value = ft_strjoin(ret_value, tmp);
			free(tmp);
			str += i;
		}
		else if (str[i] == '\"')
		else if (str[i] == '$')
	}
}