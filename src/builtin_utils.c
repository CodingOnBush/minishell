/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:13:28 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/18 13:53:19 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_isecho(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strncmp(str, "echo", len) == 0)
		return (YES);
	return (NO);
}

int	ft_iscd(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (ft_strncmp(str, "cd", len) == 0)
		return (YES);
	return (NO);
}

int	ft_isbuiltin(t_cmd *cmd)
{
	char	*str;
	int		len;

	if (!cmd || !(cmd->arg_list) || !(cmd->arg_list->value))
		return (NO);
	str = cmd->arg_list->value;
	len = ft_strlen(str);
	if (len == 0)
		return (NO);
	if (!ft_strncmp(str, "echo", len))
		return (YES);
	if (!ft_strncmp(str, "cd", len))
		return (YES);
	if (!ft_strncmp(str, "pwd", len))
		return (YES);
	if (!ft_strncmp(str, "export", len) || !ft_strncmp(str, "unset", len))
		return (YES);
	if (!ft_strncmp(str, "env", len))
		return (YES);
	if (!ft_strncmp(str, "exit", len))
		return (YES);
	if (!ft_strncmp(str, ":", len) || !ft_strncmp(str, "!", len))
		return (YES);
	return (NO);
}
