/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:13:28 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/19 15:17:43 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_cmdcmp(t_cmd *cmd, char *cmd_name)
{
	char	*str;
	int		len;

	if (!cmd || !(cmd->arg_list) || !(cmd->arg_list->value))
		return (NO);
	str = cmd->arg_list->value;
	len = ft_strlen(str);
	if (len == 0)
		return (NO);
	if (ft_strncmp(str, cmd_name, len) == 0)
		return (YES);
	return (NO);
}

int	ft_isbuiltin(t_cmd *cmd)
{
	char	*builtins[] = {"echo", "cd", "pwd",
		"export", "unset", "env", "exit", ":", "!", NULL};
	char		*str;
	int			len;
	int			i;

	if (!cmd || !(cmd->arg_list) || !(cmd->arg_list->value))
		return (NO);
	str = cmd->arg_list->value;
	len = ft_strlen(str);
	if (len == 0)
		return (NO);
	i = 0;
	while (builtins[i])
	{
		if (ft_cmdcmp(cmd, (char *)builtins[i]) == YES)
			return (YES);
		i++;
	}
	return (NO);
}
