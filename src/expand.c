/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:16:46 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/29 16:40:38 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_super_strjoin(char *extended_str, char *toadd)
{
	char	*new_str;
	int		len;
	int		i;
	int		j;

	if (toadd == NULL)
		return (extended_str);
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
	while (str[i] && ft_isspace(str[i]) == NO && ft_isquote(str[i]) == NO && ft_isalnum(str[i]) == YES)
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
	if (len == 0)
		return (NULL);
	var_name = ft_substr(str, 0, len);
	if (!var_name)
		return (NULL);
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

static char	*ft_simple_expand(char *str, int *step)
{
	char	*var_name;
	char	*var_content;

	if (!str || str[0] != '$')
		return (NULL);
	var_name = ft_get_var_name(str);
	if (!var_name)
	{
		*step = 1;
		return (ft_strdup("$"));
	}
	*step = ft_strlen(var_name) + 1;
	var_content = getenv(var_name);
	if (!var_content)
		return (NULL);
	return (var_content);
}

static char	*ft_grab_until_next_var(char *str, int *step)
{
	int		len;
	char	*res;

	len = ft_step_to_next_var(str);
	*step = 1;
	if (len == 0)
		return (NULL);
	res = ft_substr(str, 0, len);
	if (!res)
		return (NULL);
	*step = len;
	return (res);
}

static char	*ft_expand_in_double_quotes(char *str)
{
	char	*expanded_str;
	char	*toadd;
	char	*tmp;
	int		step;
	
	step = 0;
	expanded_str = NULL;
	while (*str)
	{
		if (*str == '$')
			toadd = ft_simple_expand(str, &step);
		else
			toadd = ft_grab_until_next_var(str, &step);
		tmp = ft_super_strjoin(expanded_str, toadd);
		if (!tmp)
			return (NULL);
		free(expanded_str);
		expanded_str = tmp;
		str += step;
	}
	return (expanded_str);
}

char	*ft_get_expanded_str(char *str)
{
	char	*expanded_str;
	char	*str_btw_quotes;
	char	*var_name;
	char	*toadd;
	char	*var_content;
	char	*tmp;
	int		len;
	int		i;
	int		j;
	int		step;
	
	i = 0;
	expanded_str = NULL;
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOTES)
		{
			len = ft_strchr(&str[i] + 1, DOUBLE_QUOTES) - str - i + 1;
			str_btw_quotes = ft_substr(str, i + 1, len - 2);
			if (!str_btw_quotes)
				return (NULL);
			tmp = ft_expand_in_double_quotes(str_btw_quotes);
			if (!tmp)
				return (NULL);
			expanded_str = ft_super_strjoin(expanded_str, tmp);
			if (!expanded_str)
				return (NULL);
			i += len;
		}
		else if (str[i] == SINGLE_QUOTE)
		{
			len = ft_strchr(&str[i] + 1, SINGLE_QUOTE) - str - i + 1;
			str_btw_quotes = ft_substr(str, i + 1, len - 2);
			if (!str_btw_quotes)
				return (NULL);
			expanded_str = ft_super_strjoin(expanded_str, str_btw_quotes);
			if (!expanded_str)
				return (NULL);
			i += len;
		}
		else if (str[i] == '$')
		{
			tmp = ft_simple_expand(&str[i], &i);
			if (tmp)
			{
				expanded_str = ft_super_strjoin(expanded_str, tmp);
				if (!expanded_str)
					return (NULL);
			}
			i += ft_get_var_name_size(&str[i]) + 1;
		}
		else
		{
			toadd = ft_grab_until_next_var(&str[i], &step);
			if (toadd)
			{
				printf("TOADD: [%s]\n", toadd);
				tmp = ft_super_strjoin(expanded_str, toadd);
				if (!tmp)
					return (NULL);
				free(expanded_str);
				expanded_str = tmp;
			}
			// len = ft_step_to_next_var(&str[i]);
			// if (len > 0)
			// {
			// 	tmp = ft_substr(str, i, len);
			// 	if (!tmp)
			// 		return (NULL);
			// 	expanded_str = ft_super_strjoin(expanded_str, tmp);
			// 	if (!expanded_str)
			// 		return (NULL);
			// 	i += len;
			// }
			// else
			// 	i++;
			i += step;
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
