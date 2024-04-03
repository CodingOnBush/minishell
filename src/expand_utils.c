/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 13:29:46 by momrane           #+#    #+#             */
/*   Updated: 2024/04/03 14:18:37 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

char	*ft_get_expand(char *var_name)
{
	char	*var_content;

	if (var_name == NULL)
		return (ft_strdup("$"));
	// if (*var_name == '?') // 
	// 	return (ft_itoa(g_exit_status));
	var_content = getenv(var_name);
	if (!var_content)
		return (NULL);
	return (ft_strdup(var_content));
}
