/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:29:20 by momrane           #+#    #+#             */
/*   Updated: 2024/04/06 15:58:02 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_isappend(char *str)
{
	if (!str)
		return (NO);
	if (str[0] == '>' && str[1] && str[1] == '>')
		return (YES);
	return (NO);
}

int	ft_isheredoc(char *str)
{
	if (!str)
		return (NO);
	if (str[0] == '<' && str[1] && str[1] == '<')
		return (YES);
	return (NO);
}

int	ft_isop(char *str)
{
	if (!str)
		return (NO);
	if (ft_isappend(str) || ft_isheredoc(str))
		return (YES);
	if (ft_strchr("><", *str) != NULL)
		return (YES);
	return (NO);
}

int  ft_get_type(char *str)
{
	if (*str == '|')
		return (PIPE);
	if (ft_isheredoc(str) == YES)
		return (HERE_DOC);
	if (ft_isappend(str) == YES)
		return (APPEND);
	if (*str == '<')
		return (LEFT_TRUNC);
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

int	ft_get_pipe_count(t_token *token_list)
{
	int		count;
	t_token	*tmp;

	count = 0;
	tmp = token_list;
	while (tmp)
	{
		if (tmp->type == PIPE)
			count++;
		tmp = tmp->next;
	}
	return (count);
}

char	**ft_create_args_array(t_arg *arg_list)
{
	char	**args;
	t_arg	*tmp;
	int		len;

	len = 0;
	if (!arg_list)
		return (NULL);
	tmp = arg_list;
	while (tmp)
	{
		len++;
		tmp = tmp->next;
	}
	args = (char **)malloc(sizeof(char *) * (len + 1));
	if (!args)
		return (NULL);
	len = 0;
	while (arg_list)
	{
		args[len] = arg_list->value;
		len++;
		arg_list = arg_list->next;
	}
	args[len] = NULL;
	return (args);	
}
