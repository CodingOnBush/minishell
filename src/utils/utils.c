/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:29:20 by momrane           #+#    #+#             */
/*   Updated: 2024/05/01 20:17:29 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_isappend(char *str)
{
	if (!str)
		return (NO);
	if (str[0] == '>' && str[1] && str[1] == '>')
		return (YES);
	return (NO);
}

static int	ft_isheredoc(char *str)
{
	if (!str)
		return (NO);
	if (str[0] == '<' && str[1] && str[1] == '<')
		return (YES);
	return (NO);
}

int	ft_isop(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (!str)
		return (NO);
	if (ft_strncmp(str, ">>", len) == 0)
		return (YES);
	if (ft_strncmp(str, "<<", len) == 0)
		return (YES);
	if (ft_strncmp(str, ">", len) == 0)
		return (YES);
	if (ft_strncmp(str, "<", len) == 0)
		return (YES);
	return (NO);
}

int	ft_gettype(char *str)
{
	if (*str == '|')
		return (PIPE);
	if (ft_isheredoc(str) == YES)
		return (HD);
	if (ft_isappend(str) == YES)
		return (APPEND);
	if (*str == '<')
		return (LT);
	if (*str == '>')
		return (RIGHT_TRUNC);
	return (WORD);
}

int	ft_isoperator(char *str)
{
	if (!str)
		return (NO);
	if (ft_isappend(str) || ft_isheredoc(str))
		return (2);
	if (ft_strchr("|><", *str) != NULL)
		return (1);
	return (NO);
}
