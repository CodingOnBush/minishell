/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:32:20 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 12:32:21 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

	grab = NULL;
	res = NULL;
	if (str && ft_isquote(*str) && (str + 1))
	{
		res = ft_grab_next_quotes(data, str);
		if (!res)
			return (ft_strdup("\0"));
	}
	else if (str && *str == '$' && (str + 1))
	{
		grab = ft_grab_var_name(str);
		res = ft_get_expand(data, grab, str);
		free(grab);
	}
	else
		res = ft_grab_str(str, " \t\n\r\v\f$\'\"");
	return (res);
}

char	*ft_get_expanded_str(t_data *data, char *str)
{
	char	*res;
	char	*tmp;
	char	*next_str;

	res = NULL;
	next_str = NULL;
	if (ft_strncmp(str, "~/", 2) == 0 || ft_strcmp(str, "~") == 0)
	{
		next_str = ft_getenv(data->env_list, "HOME");
		str++;
		tmp = ft_super_strjoin(res, next_str);
		res = tmp;
	}
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
			if (ft_strchr(token->value, '\'') != NULL || ft_strchr(token->value,
					'\"') != NULL)
				token->to_expand = false;
			new_str = ft_remove_quotes(token->value);
			free(token->value);
			token->value = new_str;
		}
		token = token->next;
	}
}
