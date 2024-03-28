/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:16:46 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/28 11:08:30 by vvaudain         ###   ########.fr       */
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

int	dist_to_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\'')
		i++;
	return (i);
}

char	*ft_get_vars(char *str)
{
	int		i;
	int		j;
	char	*ret_value;
	char	*tmp;
	char	*var_value;

	if (!str)
		return (NULL);
	i = 0;
	ret_value = NULL;
	tmp = NULL;
	while (*str)
	{
		i = 0;
		while (str[i] && str[i] != '\'' && str[i] != '\"' && str[i] != '$')
			i++;
		if (i != 0 && str[i] != NULL)
		{
			ft_strlcpy(tmp, *str, i + 1); // voir si ok de mettre i + 1 et si pas i + 2
			ret_value = ft_strjoin(ret_value, tmp);
			free(tmp);
			str += i;
		}
		else
			return (ret_value);
		if (str[i] == '\'')
		{
			str++;
			if (*str)
			{
				i = dist_to_quote(*str); // coder la fonction dist_to_quote
				ft_strlcpy(tmp, str, i);
				ret_value = ft_strjoin(ret_value, tmp);
				free(tmp);
				str += i;
			}
			else
				return (ret_value);
		}
		else if (str[i] == '\"')
		{
			i++;
			str++;
			j = i;
			while (str[j] && str[j] != '$' && str[j] != '\"')
				j++;
			if (j - i != 0 && str[j] != NULL)
			{
				ft_strlcpy(tmp, str, j - i + 1);
				ret_value = ft_strjoin(ret_value, tmp);
				free(tmp);
				str += j - i + 1;
			}
			else
				return (ret_value);
			i = j;
			if (str[j] && str[j] == '$')
			{
				while (str[j] && str[j] != '\"' && ft_isspace(str[j]) == NO)
					j++;
				if (str[j] != NULL && ft_isspace(str[j]) == YES)
				{
					ft_strlcpy(tmp, str, j - i + 1);
					var_value = ft_strdup(getenv((const)tmp));
					ret_value = ft_strjoin(ret_value, var_value);
					free(tmp);
					free(var_value);
					j++;
					str += j;
					i = j;
					while (str[j] && str[j] != '\"')
						j++;
					if (j - i != 0 && str[j])
					{
						ft_strlcpy(tmp, str, j - i + 1);
						ret_value = ft_strjoin(ret_value, tmp);
						free(tmp);
						str += j - i + 1;
					}
					str += j;
					i = j;
				}
				else if (str[j] && str[j] == '\"')
				{
					ft_strlcpy(tmp, str, j - i + 1);
					var_value = ft_strdup(getenv((const)tmp));
					ret_value = ft_strjoin(ret_value, var_value);
					free(tmp);
					free(var_value);
					str += j;
					i = j;
				}
				else
					return (ret_value);
			}
			
		}
		else if (str[i] == '$')
		{
			i++;
			while (str[i] && str[i] != '\"' && ft_isspace(str[i]) == NO)
				i++;
			
		}
	}
}
