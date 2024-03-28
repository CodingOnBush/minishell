/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:16:46 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/28 19:11:12 by vvaudain         ###   ########.fr       */
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

char	*get_var_name(char *str, bool *single_quote_is_char)
{
	int		i;
	char	*var_name;
	
	i = 0;
	if (!str)
		return (NULL);
	if (str[i] == '$')
		i++;
	while (str[i] && ft_isspace(str[i]) == NO && str[i] != DOUBLE_QUOTES && str[i] != SINGLE_QUOTE)
		i++;
	if (str[i] == DOUBLE_QUOTES && *single_quote_is_char == true)
		*single_quote_is_char = !*single_quote_is_char;
	if (i <= 1)
		return (NULL);
	var_name = malloc(sizeof(char) * (i + 1));
	if (!var_name)
		return (NULL);
	ft_strlcpy(var_name, str + 1, i);
	return (var_name);
}

char	*ft_concat(char *res, char *str, int size)
{
	char	*new_res;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(res) + size;
	new_res = malloc(sizeof(char) * (len + 1));
	if (!new_res)
		return (NULL);
	i = 0;
	while (i < ft_strlen(res))
	{
		new_res[i] = res[i];
		i++;
	}
	j = 0;
	while (i < len)
	{
		new_res[i] = str[j];
		i++;
		j++;
	}
	new_res[i] = '\0';
	return (new_res);
}

static char	*dollar_handling(t_data *data, char *str, bool *single_quote_is_char)
{
	char	*new_res;
	char	*var_name;
	char	*var_content;

	data->step = 0;
	var_name = get_var_name(str, single_quote_is_char);
	if (var_name != NULL)
	{
		var_content = getenv(var_name);
		if (var_content != NULL)
		{
			new_res = ft_concat(new_res, var_content, ft_strlen(var_content));
			if (!new_res)
				return (NULL);
		}
		data->step += ft_strlen(get_var_name(str, single_quote_is_char)) + 1;
	}
	else
	{
		new_res = ft_concat(new_res, str, 1);
		if (!new_res)
			return (NULL);
		data->step += 1;
	}
	return (new_res);
}

static char	*handle_single_quote(t_data *data, char *str)
{
	char	*new_res;

	data->step = ft_strchr(str + 1, SINGLE_QUOTE) - str + 1;
	new_res = ft_concat(new_res, str, data->step);
	if (!new_res)
		return (NULL);
	return (new_res);
}

// static char	*handle_normal_text(t_data *data, char *str, int i, bool *single_quote_is_char)
// {
// 	char	*new_res;
// 	char	*tmp;
	
// 	data->step = 0;
// 	tmp = str;
// 	while (*str && *str != '$' && *str != SINGLE_QUOTE && *str != DOUBLE_QUOTES)
// 	{
// 		str++;
// 		data->step++;
// 	}
// 	if (*str == DOUBLE_QUOTES)
// 	{
// 		*single_quote_is_char = !(*(single_quote_is_char));
// 		str++;
// 		data->step++;
// 	}
// 	if (*str == SINGLE_QUOTE && *single_quote_is_char == true)
// 	{
// 		str++;	
// 		data->step++;
// 	}
// 	if (data->step > 0)
// 	{
// 		new_res = ft_concat(new_res, tmp, data->step);
// 		if (!new_res)
// 			return (NULL);
// 	}
// 	return (new_res);
// }

static char	*ft_get_extend(char *str, t_data *data)
{
	int		i;
	int		len;
	char	*res;
	bool	single_quote_is_char;

	i = 0;
	res = NULL;
	single_quote_is_char = false;
	while (str[i] != '\0')
	{
		len = i;
		// res = handle_normal_text(data, &str[len], i, &single_quote_is_char);
		// if (!res)
		// 	return (NULL);
		// i += data->step;
		while (str[len] && str[len] != '$' && str[len] != SINGLE_QUOTE && str[len] != DOUBLE_QUOTES)
			len++;
		if (str[len] == DOUBLE_QUOTES)
		{
			single_quote_is_char = !single_quote_is_char;
			len++;
		}
		if (str[len] == SINGLE_QUOTE && single_quote_is_char == true)
			len++;
		if (len > i)
		{
			res = ft_concat(res, &str[i], len - i);
			if (!res)
				return (NULL);
			i += len - i;
		}
		if (str[i] == '$')
		{
			res = dollar_handling(data, &str[i], &single_quote_is_char);
			i += data->step;
		}
		else if (str[i] == SINGLE_QUOTE && single_quote_is_char == false)
		{
			res = handle_single_quote(data, &str[i]);
			i += data->step;
		}
	}
	return (res);
}

int	ft_check_expands(t_token *list, t_data *data)
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
			cur_token->str = ft_get_extend(tmp, data);
			if (cur_token->str == NULL)
				return (FAIL);
			printf("str expanded: %s\n", cur_token->str);
			free(tmp);
		}
		cur_token = cur_token->next;
	}
	return (SUCCESS);
}
