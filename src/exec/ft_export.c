/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:48:28 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 09:50:22 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_print(char *msg, int fd)
{
	ft_putstr_fd("minishell: ", fd);
	ft_putstr_fd(msg, fd);
	ft_putstr_fd("\n", fd);
}

static int	ft_is_an_option(char *str)
{
	if (!str || str[0] != '-')
		return (NO);
	if (ft_strcmp(str, "--") == 0 || ft_strcmp(str, "-") == 0)
		return (NO);
	if (ft_strncmp(str, "--", 2) == 0 && str[2] != '\0')
		return (YES);
	if (ft_strncmp(str, "-", 1) == 0 && str[1] != '\0')
		return (YES);
	return (NO);
}

int	ft_export(t_data *data, t_cmd *cmd)
{
	t_arg	*args;
	int		exit_status;

	exit_status = 0;
	if (!data || !cmd || !cmd->arg_list || !cmd->arg_list->value)
		return (FAIL);
	args = cmd->arg_list;
	if (args->next == NULL)
		return (ft_print_exports_var(data), 0);
	args = args->next;
	if (ft_strcmp(args->value, "--") == 0 && args->next == NULL)
		return (ft_print_exports_var(data), 0);
	if (ft_strcmp(args->value, "--") == 0 && args->next != NULL)
		args = args->next;
	if (ft_is_an_option(args->value) == YES)
		return (ft_print("export: options are not allowed", 2), 2);
	while (args)
	{
		if (ft_handle_line(data, args->value) == FAIL)
			exit_status = 1;
		args = args->next;
	}
	return (exit_status);
}
