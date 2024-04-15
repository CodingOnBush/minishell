/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:13:28 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/15 07:32:56 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_isbuiltin(t_cmd *cmd)
{
	char	*cmd_name;
	int		len;

	if (!cmd || !(cmd->arg_list) || !(cmd->arg_list->value))
		return (NO);
	cmd_name = cmd->arg_list->value;
	len = ft_strlen(cmd_name);
	if (ft_strncmp(cmd_name, "echo", len) == 0)
		return (YES);
	if (ft_strncmp(cmd_name, "cd", len) == 0)
		return (YES);
	if (ft_strncmp(cmd_name, "pwd", len) == 0)
		return (YES);
	if (ft_strncmp(cmd_name, "export", len) == 0)
		return (YES);
	if (ft_strncmp(cmd_name, "unset", len) == 0)
		return (YES);
	if (ft_strncmp(cmd_name, "env", len) == 0)
		return (YES);
	if (ft_strncmp(cmd_name, "exit", len) == 0)
		return (YES);
	if (ft_strncmp(cmd_name, ":", len) == 0)
	{
		// printf("YES\n");
		return (YES);
	}
	if (ft_strncmp(cmd_name, "!", len) == 0)
		return (YES);
	return (NO);
}

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
