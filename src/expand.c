/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:16:46 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/29 15:57:39 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* static int	dist_to_quote(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '\'')
		i++;
	return (i);
}

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
} */

static char	*ft_super_strjoin(char *extended_str, char *toadd)
{
	char	*new_str;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(extended_str) + ft_strlen(toadd);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < ft_strlen(extended_str))
	{
		new_str[i] = extended_str[i];
		i++;
	}
	j = 0;
	while (i < len)
	{
		new_str[i] = toadd[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}

static int	ft_get_var_name_size(char *str)
{
	int		i;

	i = 0;
	if (!str)
		return (0);
	if (*str == '$')
		str++;
	while (str[i] && ft_isspace(str[i]) == NO && ft_isquote(str[i]) == NO && ft_isalnum(str[i]) == YES)// str[i] != '$'
		i++;
	return (i);
}

static char	*ft_get_var_name(char *str)
{
	int		len;
	char	*var_name;

	if (!str)
		return (NULL);
	if (*str == '$')
		str++;
	if (*str == '$')
		return (NULL);
	len = ft_get_var_name_size(str);
	// printf("len: %d\n", len);
	if (len == 0)
		return (NULL);
	var_name = ft_substr(str, 0, len);
	if (!var_name)
		return (NULL);
	printf("var_name: %s\n", var_name);
	return (var_name);
}

static int	ft_step_to_next_var(char *str)
{
	int		i;

	i = 0;
	while (str[i] && str[i] != '$' && str[i] != DOUBLE_QUOTES)
		i++;
	return (i);
}

static char	*ft_simple_expand(char *str)
{
	char	*var_name;
	char	*var_content;

	if (!str || str[0] != '$')
		return (NULL);
	var_name = ft_get_var_name(str);
	if (!var_name)
		return (ft_strdup("$"));
	var_content = getenv(var_name);
	if (!var_content)
		return (NULL);
	return (var_content);
}

static char	*ft_expand_in_double_quotes(char *str)
{
	char	*expanded_str;
	char	*tmp;
	int		j;
	int		i;
	int		len;
	
	i = 0;
	expanded_str = NULL;
	// printf("str: %s\n", str);
	while (str[i] != '\0')
	{
		if (str[i] == '$')
		{
			tmp = ft_simple_expand(&str[i]);
			if (tmp != NULL)
			{
				expanded_str = ft_super_strjoin(expanded_str, tmp);
				if (!expanded_str)
					return (NULL);
			}
			i += ft_get_var_name_size(&str[i]) + 1;
		}
		else
		{
			len = ft_step_to_next_var(str + i);
			if (len > 0)
			{
				tmp = ft_substr(str, i, len);
				if (!tmp)
					return (NULL);
				expanded_str = ft_super_strjoin(expanded_str, tmp);
				if (!expanded_str)
					return (NULL);
				i += len;
			}
			else
				i++;
		}
	}
	// printf("expanded_str: %s\n", expanded_str);
	return (expanded_str);
}

char	*ft_get_expanded_str(char *str)
{
	char	*expanded_str;
	char	*str_btw_quotes;
	char	*var_name;
	char	*var_content;
	char	*tmp;
	int		len;
	int		i;
	int		j;
	
	i = 0;
	expanded_str = NULL;
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOTES)
		{
			// printf("here is where we are in the string: %s\n", &str[i]);
			len = ft_strchr(str + i + 1, DOUBLE_QUOTES) - str - i + 1;
			// printf("size of the string with the double quotes: %d\n", len);
			// printf("STRRRR: %s\n", str);
			// printf("len: %d\n", len);
			str_btw_quotes = ft_substr(str, i + 1, len - 2);
			if (!str_btw_quotes)
				return (NULL);
			printf("content of the double quotes: %s\n", str_btw_quotes);
			if (ft_strchr(str_btw_quotes, '$') != NULL)
			{
				// printf("there is a dollar in the double quotes\n");
				// printf("lets get the expanded string\n");
				tmp = ft_expand_in_double_quotes(str_btw_quotes);
				if (!tmp)
					return (NULL);
				// printf("expanded string: %s\n", tmp);
				expanded_str = ft_super_strjoin(expanded_str, tmp);
				if (!expanded_str)
					return (NULL);
				// printf("expanded_str: %s\n", expanded_str);
			}
			else
			{
				expanded_str = ft_super_strjoin(expanded_str, str_btw_quotes);
				if (!expanded_str)
					return (NULL);
			}
			i += len;
		}
		else if (str[i] == SINGLE_QUOTE)
		{
			len = ft_strchr(str + i + 1, SINGLE_QUOTE) - str - i + 1;
			// printf("size of the string with the single quotes: %d\n", len);
			str_btw_quotes = ft_substr(str, i + 1, len - 2);
			if (!str_btw_quotes)
				return (NULL);
			// printf("content of the single quotes: %s\n", str_btw_quotes);
			expanded_str = ft_super_strjoin(expanded_str, str_btw_quotes);
			if (!expanded_str)
				return (NULL);
			// printf("expanded_str: %s\n", expanded_str);
			i += len;
		}
		else if (str[i] == '$')
		{
			tmp = ft_simple_expand(str + i);
			if (tmp != NULL)
			{
				expanded_str = ft_super_strjoin(expanded_str, tmp);
				if (!expanded_str)
					return (NULL);
			}
			i += ft_get_var_name_size(str + i) + 1;
		}
		else
		{
			len = ft_step_to_next_var(&str[i]);
			if (len > 0)
			{
				tmp = ft_substr(str, i, len);
				if (!tmp)
					return (NULL);
				expanded_str = ft_super_strjoin(expanded_str, tmp);
				if (!expanded_str)
					return (NULL);
				i += len;
			}
			else
				i++;
		}
	}
	return (expanded_str);
}

int	ft_expand(t_data *data)
{
	t_token	*token;
	char	*expanded_str;

	token = data->token_list;
	if (token == NULL)
		return (SUCCESS);
	while (token)
	{
		if (token->type == WORD)
		{
			expanded_str = ft_get_expanded_str(token->str);
			if (!expanded_str)
				return (FAIL);
			printf("->[%s]\n", expanded_str);
			free(token->str);
			token->str = expanded_str;
		}
		token = token->next;
	}
	return (SUCCESS);
}
