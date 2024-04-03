/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 17:13:28 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/03 18:34:02 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_isbuiltin(char *cmd)
{
	int	len;

	len = ft_strlen(cmd);
	if (len == 0)
		return (NO);
	if (ft_strncmp(cmd, "echo", len) == 0)
		return (YES);
	if (ft_strncmp(cmd, "cd", len) == 0)
		return (YES);
	if (ft_strncmp(cmd, "pwd", len) == 0)
		return (YES);
	if (ft_strncmp(cmd, "export", len) == 0)
		return (YES);
	if (ft_strncmp(cmd, "unset", len) == 0)
		return (YES);
	if (ft_strncmp(cmd, "env", len) == 0)
		return (YES);
	if (ft_strncmp(cmd, "exit", len) == 0)
		return (YES);
	return (NO);
}
