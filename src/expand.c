/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:16:46 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/02 17:42:52 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_in_var(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (YES);
	return (NO);
}

char	*ft_remove_quotes(char *str)
{
	char	*new_str;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	if (*str == SINGLE_QUOTE || *str == DOUBLE_QUOTES)
		i++;
	new_str = ft_substr(str, i, ft_strlen(str) - 2 * i);
	return (new_str);
}

char	*ft_super_strjoin(char *extended_str, char *toadd)
{
	char	*join;
	int		new_len;
	int		extended_len;
	int		toadd_len;
	int		i;

	if (extended_str == NULL && toadd == NULL)
		return (NULL);
	i = 0;
	extended_len = ft_strlen(extended_str);
	toadd_len = ft_strlen(toadd);
	new_len = extended_len + toadd_len;
	join = malloc(sizeof(char) * (new_len + 1));
	if (!join)
		return (NULL);
	if (extended_str)
	{
		i = -1;
		while (extended_str[++i])
			join[i] = extended_str[i];
	}
	if (toadd)
	{
		i = -1;
		while (toadd[++i])
			join[extended_len + i] = toadd[i];
	}
	join[new_len] = '\0';
	return (join);
}

char	*ft_get_expand(char *var_name)
{
	char	*var_content;

	if (!var_name)
		return (ft_strdup("$"));
	// if (*var_name == '?') // 
	// 	return (ft_itoa(g_exit_status));
	var_content = getenv(var_name);
	if (!var_content)
		return (NULL);
	return (var_content);
}

char *ft_grab_str(char *str, char *limset)
{
	char	*grab;
	int		i;

	if (!str)
		return (NULL);
	i = 0;
	while (str[i] && ft_strchr(limset, str[i]) == NULL)
		i++;
	if (i == 0)
		return (NULL);
	grab = ft_substr(str, 0, i);
	return (grab);
}

char	*ft_grab_var_name(char *str)
{
	int		i;
	char	*var_name;

	if (!str || *str != '$')
		return (NULL);
	str++;
	if (str && *str == '?')
		return (ft_strdup("?"));
	i = 0;
	while (str[i] && ft_is_in_var(str[i]))
		i++;
	if (i == 0)
		return (NULL);
	var_name = ft_substr(str, 0, i);
	return (var_name);
}

char	*ft_get_next_str_in_double_quotes(char *str)
{
	char	*var_name;
	char	*new_str;
	char	*toadd;
	char	*tmp;
	
	new_str = NULL;
	if (!str)
		return (NULL);
	toadd = NULL;
	while (*str != '\0')
	{
		if (str && *str == '$')// && (str + 1)) // est-ce qu'on garde cette condition ?
		{
			var_name = ft_grab_var_name(str);
			str += ft_strlen(var_name) + 1;
			toadd = ft_get_expand(var_name);
			free(var_name);
			tmp = ft_super_strjoin(new_str, toadd);
			free(new_str);
			// free(toadd);
			new_str = tmp;
		}
		else
		{
			toadd = ft_grab_str(str, "$\"");
			str += ft_strlen(toadd);
			tmp = ft_super_strjoin(new_str, toadd);
			free(toadd);
			free(new_str);
			new_str = tmp;
		}
	}
	return (new_str);
}

int	ft_get_next_step(char *str, char *new_str)
{
	char	*grab;
	int		res;

	if (!str || *str == '\0')
		return (0);
	if ((*str == DOUBLE_QUOTES || *str == SINGLE_QUOTE) && (str + 1))
		return (ft_strchr(str + 1, *str) - str + 1);
	if (*str == '$')
	{
		grab = ft_grab_var_name(str);
		res = ft_strlen(grab) + 1;
		free(grab);
		return (res);
	}
	return (ft_strlen(new_str));
}

char	*ft_get_next_str(char *str)
{
	char	*grab;
	char	*res;

	if (str && *str == SINGLE_QUOTE && (str + 1))
		return (ft_grab_str(str + 1, "\'"));
	if (str && *str == DOUBLE_QUOTES && (str + 1))
	{
		grab = ft_grab_str(str + 1, "\"");
		res = ft_get_next_str_in_double_quotes(grab);
		return (free(grab), res);
	}
	if (str && *str == '$' && (str + 1))
	{
		grab = ft_grab_var_name(str);
		res = ft_get_expand(grab);
		return (free(grab), res);
	}
	return (ft_grab_str(str, " \t\n\r\v\f$\'\""));
}

char	*ft_get_expanded_str(char *str)
{
	char	*res;
	char	*tmp;
	char	*next_str;
	
	res = NULL;
	next_str = NULL;
	while (*str != '\0')
	{
		next_str = ft_get_next_str(str);
		tmp = ft_super_strjoin(res, next_str);
		free(res);
		str += ft_get_next_step(str, next_str);
		free(next_str);
		res = tmp;
	}
	return (res);
}

int	ft_expand(t_data *data)
{
	t_token	*token;
	char	*new_str;

	token = data->token_list;
	if (token == NULL)
		return (SUCCESS);
	new_str = NULL;
	while (token)
	{
		if (token->type == WORD)
		{
			new_str = ft_get_expanded_str(token->str);
			free(token->str);
			token->str = new_str;
		}
		else if (token->type == LIM)
		{
			new_str = ft_remove_quotes(token->str);
			if (!new_str)
				return (FAIL);
			free(token->str);
			token->str = new_str;
		}
		token = token->next;
	}
	// ft_remove_null_token(data);
	return (SUCCESS);
}
