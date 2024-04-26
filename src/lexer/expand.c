/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 01:13:46 by allblue           #+#    #+#             */
/*   Updated: 2024/04/26 11:45:10 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_get_next_str_in_double_quotes(t_data *data, char *str)
{
	char	*var_name;
	char	*new_str;
	char	*toadd;
	char	*tmp;

	new_str = NULL;
	toadd = NULL;
	while (str != NULL && *str != '\0')
	{
		if (str && *str == '$')
		{
			var_name = ft_grab_var_name(str);
			toadd = ft_get_expand(data, var_name, str);
			str += ft_strlen(var_name) + 1;
			free(var_name);
		}
		else
		{
			toadd = ft_grab_str(str, "$\"");
			str += ft_strlen(toadd);
		}
		tmp = ft_super_strjoin(new_str, toadd);
		new_str = tmp;
	}
	return (new_str);
}

static int	ft_get_next_step(char *str, char *new_str)
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

static char	*ft_grab_next_str(t_data *data, char *str)
{
	char	*grab;
	char	*res;

	if (str && *str == SINGLE_QUOTE && (str + 1))
	{
		grab = ft_grab_str(str + 1, "\'");
		if (!grab)
			return (ft_strdup("\0"));
		return (grab);
	}
	if (str && *str == DOUBLE_QUOTES && (str + 1))
	{
		grab = ft_grab_str(str + 1, "\"");
		res = ft_get_next_str_in_double_quotes(data, grab);
		free(grab);
		if (!res)
			return (ft_strdup("\0"));
		return (res);
	}
	if (str && *str == '$' && (str + 1))
	{
		grab = ft_grab_var_name(str);
		res = ft_get_expand(data, grab, str);
		free(grab);
		return (res);
	}
	grab = ft_grab_str(str, " \t\n\r\v\f$\'\"");
	return (grab);
}

char	*ft_get_expanded_str(t_data *data, char *str)
{
	char	*res;
	char	*tmp;
	char	*next_str;

	res = NULL;
	next_str = NULL;
	while (*str != '\0')
	{
		next_str = ft_grab_next_str(data, str);
		str += ft_get_next_step(str, next_str);
		tmp = ft_super_strjoin(res, next_str);
		res = tmp;
	}
	return (res);
}

void	ft_expand(t_data *data, t_token **token_list)
{
	t_token	*token;
	char	*new_str;

	new_str = NULL;
	token = *token_list;
	while (token != NULL)
	{
		if (token->type == WORD)
		{
			new_str = ft_get_expanded_str(data, token->value);
			free(token->value);
			token->value = new_str;
		}
		else if (token->type == LIM)
		{
			new_str = ft_remove_quotes(token->value);
			free(token->value);
			token->value = new_str;
		}
		token = token->next;
	}
}
