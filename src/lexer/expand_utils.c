/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:29:46 by momrane           #+#    #+#             */
/*   Updated: 2024/05/01 17:19:10 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_count_quotes(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i] == SINGLE_QUOTE || str[i] == DOUBLE_QUOTES)
			count++;
		i++;
	}
	return (count);
}

char	*ft_remove_quotes(char *str)
{
	char	*new_str;
	int		i;
	int		quotes;

	i = 0;
	quotes = ft_count_quotes(str);
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - quotes + 1));
	if (!new_str)
		return (NULL);
	while (str && *str)
	{
		if (*str != SINGLE_QUOTE && *str != DOUBLE_QUOTES)
		{
			new_str[i] = *str;
			i++;
		}
		str++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_grab_str(char *str, char *limset)
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
	if (ft_isdigit(*str))
		return (ft_substr(str, 0, 1));
	i = 0;
	while (str[i] && ft_is_in_var(str[i]))
		i++;
	if (i == 0)
		return (NULL);
	var_name = ft_substr(str, 0, i);
	return (var_name);
}

char	*ft_get_expand(t_data *data, char *var_name, char *str)
{
	char	*var_content;

	if (var_name == NULL)
	{
		if (ft_is_in_var(*(str + 1)) == NO && ft_isquote(*(str + 1)) == NO)
			return (ft_strdup("$"));
		return (NULL);
	}
	if (*var_name == '?')
		return (ft_itoa(data->exit_status));
	var_content = ft_getenv(data->env_list, var_name);
	if (!var_content)
		return (NULL);
	return (var_content);
}
