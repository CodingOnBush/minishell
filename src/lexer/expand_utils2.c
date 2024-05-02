/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 09:16:20 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 09:25:24 by momrane          ###   ########.fr       */
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

char	*ft_grab_next_quotes(t_data *data, char *str)
{
	char	*grab;
	char	*res;

	grab = NULL;
	res = NULL;
	if (str && *str == SINGLE_QUOTE && (str + 1))
		res = ft_grab_str(str + 1, "\'");
	else if (str && *str == DOUBLE_QUOTES && (str + 1))
	{
		grab = ft_grab_str(str + 1, "\"");
		res = ft_get_next_str_in_double_quotes(data, grab);
		free(grab);
	}
	else
		return (NULL);
	return (res);
}
