/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:16:46 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/28 12:51:08 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	is_dollar(char *str)
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

static int	dist_to_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\'')
		i++;
	return (i);
}

// static char	*ft_get_vars(char *str)
// {
// 	int		i;
// 	int		j;
// 	char	*ret_value;
// 	char	*tmp;
// 	char	*var_value;

// 	if (!str)
// 		return (NULL);
// 	i = 0;
// 	ret_value = NULL;
// 	tmp = NULL;
// 	while (str[i])
// 	{
// 		j = i;
// 		while (str[j] && str[j] != '\'' && str[j] != '\"' && str[j] != '$')
// 			j++;
// 		if (j != 0 && str[j])
// 		{
// 			ft_strlcpy(tmp, &str[i], j - i); // voir si ok de mettre i + 1 et si pas i + 2
// 			ret_value = ft_strjoin(ret_value, tmp);
// 			free(tmp);
// 			i = j;
// 		}
// 		if (str[j] == '\'')
// 		{
// 			j++;
// 			i = j;
// 			if (str[j])
// 			{
// 				j = dist_to_quote(&str[i]); // coder la fonction dist_to_quote
// 				ft_strlcpy(tmp, &str[i], j - i);
// 				ret_value = ft_strjoin(ret_value, tmp);
// 				free(tmp);
// 				i = i + j; //+ 1?
// 				j = i;
// 			}
// 			else
// 				return (ret_value);
// 		}
// 		else if (str[j] == '\"')
// 		{
// 			j++;
// 			i = j;
// 			while (str[j] && str[j] != '$' && str[j] != '\"')
// 				j++;
// 			if (j - i != 0 && str[j])
// 			{
// 				ft_strlcpy(tmp, &str[i], j - i);
// 				ret_value = ft_strjoin(ret_value, tmp);
// 				free(tmp);
// 				j++;
// 				i = j;
// 			}
// 			else
// 				return (ret_value);
// 			if (str[j] && str[j] == '$')
// 			{
// 				while (str[j] && str[j] != '\"' && ft_isspace(str[j]) == NO)
// 					j++;
// 				if (str[j] && ft_isspace(str[j]) == YES)
// 				{
// 					ft_strlcpy(tmp, &str[i], j - i);
// 					var_value = ft_strdup(getenv(tmp));
// 					ret_value = ft_strjoin(ret_value, var_value);
// 					free(tmp);
// 					free(var_value);
// 					j++;
// 					i = j;
// 					while (str[j] && str[j] != '\"')
// 						j++;
// 					if (j - i != 0 && str[j])
// 					{
// 						ft_strlcpy(tmp, &str[i], j - i);
// 						ret_value = ft_strjoin(ret_value, tmp);
// 						free(tmp);
// 						j++;
// 						i = j;
// 					}
// 				}
// 				else if (str[j] && str[j] == '\"')
// 				{
// 					ft_strlcpy(tmp, &str[i], j - i);
// 					var_value = ft_strdup(getenv(tmp));
// 					ret_value = ft_strjoin(ret_value, var_value);
// 					free(tmp);
// 					free(var_value);
// 					j++;
// 					i = j;
// 				}
// 				else
// 					return (ret_value);
// 			}
			
// 		}
// 		else if (str[j] && str[j] == '$')
// 		{
// 			j++;
// 			i = j;
// 			while (str[j] && ft_isspace(str[j]) == NO)
// 				j++;
// 			tmp =  
// 			ft_strlcpy(tmp, &str[i], j - i);
// 			var_value = ft_strdup(getenv(tmp));
// 			ret_value = ft_strjoin(ret_value, var_value);
// 			free(tmp);
// 			free(var_value);
// 			if (!str[j])
// 				return (ret_value);
// 		}
// 		i++;
// 	}
// 	return (ret_value);
// }

char	*get_var_name(char *str)
{
	int		i;
	char	*var_name;
	
	i = 0;
	if (!str)
		return (NULL);
	if (str[i] == '$')
		i++;
	while (str[i] && ft_isspace(str[i]) == NO && str[i] != DOUBLE_QUOTES)
		i++;
	if (i <= 1)
		return (NULL);
	var_name = malloc(sizeof(char) * (i + 1));
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, str + 1, i);
	return (var_name);
}

static char	*ft_get_vars(char *str)
{
	char	*tmp;
	char	*ret_value;
	char	*var_str;
	char	*var_content;
	int		i;
	char	*before;
	
	i = 0;
	ret_value = NULL;
	while (str[i])
	{
		if (str[i] == '$')
		{
			var_str = get_var_name(&str[i]);
			if (!var_str)
				return (NULL);
			var_content = getenv(var_str);
			if (var_content != NULL)
			{
				printf("var_content: %s\n", var_content);
				// ft_qqch(str, i, var_content);
				if (ret_value == NULL)
				{
					ret_value = malloc(sizeof(char) * (i + 1));
					if (!ret_value)
						return(free(var_str), NULL);
					ft_strlcat(ret_value, str, i + 1);
				}
				ret_value = ft_strjoin(ret_value, var_content);
				printf("ret value : %s\n", ret_value);
			}
			i += ft_strlen(var_str);
		}
		else
			i++;
	}
	return (ret_value);
}


int	ft_check_expands(t_token *list)
{
	t_token	*cur_token;
	char	*tmp;

	if (!list)
		return (FAIL);
	cur_token = list;
	while (cur_token != NULL)
	{
		if (cur_token->type == WORD && is_dollar(cur_token->str) == YES)
		{
			tmp = cur_token->str;
			cur_token->str = ft_get_vars(tmp);
			printf("str expanded: %s\n", cur_token->str);
			if (cur_token->str == NULL)
				return (FAIL);
			free(tmp);
		}
		cur_token = cur_token->next;
	}
	return (SUCCESS);
}
