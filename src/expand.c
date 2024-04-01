/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:16:46 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/01 13:37:08 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_is_in_var(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (YES);
	return (NO);
}

char	*ft_super_strjoin(char *extended_str, char *toadd)
{
	char	*join;
	int		new_len;
	int		extended_len;
	int		toadd_len;

	if (extended_str == NULL && toadd == NULL)
		return (NULL);
	if (toadd == NULL)
		return (extended_str);
	if (extended_str == NULL)
		return (toadd);
	new_len = ft_strlen(extended_str) + ft_strlen(toadd);
	join = malloc(sizeof(char) * (new_len + 1));
	if (!join)
		return (NULL);
	extended_len = ft_strlen(extended_str);
	toadd_len = ft_strlen(toadd);
	ft_strlcpy(join, extended_str, extended_len + 1);
	ft_strlcpy(&join[extended_len], toadd, toadd_len + 1);
	// free(extended_str);
	// free(toadd);
	return (join);
}

char	*ft_get_expand(char *var_name)
{
	char	*var_content;

	if (!var_name)
		return (ft_strdup("$"));
	// if (*var_name == '?')
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
	grab = malloc(sizeof(char) * (i + 1));
	if (!grab)
		return (NULL);
	ft_strlcpy(grab, str, i + 1);
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
	
	new_str = NULL;
	if (!str)
		return (NULL);
	while (*str != '\0')
	{
		if (str && *str == '$')// && (str + 1)) // est-ce qu'on garde cette condition ?
		{
			var_name = ft_grab_var_name(str);
			str += ft_strlen(var_name) + 1;
			toadd = ft_get_expand(var_name);
			free(var_name);
		}
		else
		{
			toadd = ft_grab_str(str, "$\"");
			str += ft_strlen(toadd);
		}
		new_str = ft_super_strjoin(new_str, toadd);
		if (!new_str)
			return (NULL);
	}
	return (new_str);
}

int	ft_get_next_step(char *str, char *new_str)
{
	if (*str == '\0')
		return (0);
	if (*str == DOUBLE_QUOTES || *str == SINGLE_QUOTE)
		return (ft_strchr(str + 1, *str) - str + 1);
	else if (*str == '$')
		return (ft_strlen(ft_grab_var_name(str)) + 1);
	else
		return (ft_strlen(new_str));
}

char	*ft_get_next_str(char *str)
{
	int		i;

	if (str && *str == SINGLE_QUOTE && (str + 1))
		return (ft_grab_str(str + 1, "\'"));
	if (str && *str == DOUBLE_QUOTES && (str + 1))
		return (ft_get_next_str_in_double_quotes(ft_grab_str(str + 1, "\"")));
	if (str && *str == '$' && (str + 1))
		return (ft_get_expand(ft_grab_var_name(str)));
	if (str && ft_isspace(*str))
	{
		i = 0;
		while (str[i] && ft_isspace(str[i]))
			i++;
		return (ft_substr(str, 0, i));
	}
	return (ft_grab_str(str, " \t\n\r\v\f$\'\""));
}

char	*ft_get_new_str(char *str)
{
	char	*new_str;
	char	*next_str;
	
	new_str = NULL;
	while (*str != '\0')
	{
		next_str = ft_get_next_str(str);
		new_str = ft_super_strjoin(new_str, next_str);
		str += ft_get_next_step(str, new_str);
	}
	return (new_str);
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
			expanded_str = ft_get_new_str(token->str);
			if (!expanded_str)
				return (FAIL);
			free(token->str);
			token->str = expanded_str;
		}
		// else if (token->type == LIM)
		// {
		// 	// only remove quotes
		// }
		token = token->next;
	}
	return (SUCCESS);
}
