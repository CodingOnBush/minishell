/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 23:58:21 by allblue           #+#    #+#             */
/*   Updated: 2024/04/20 00:44:52 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_pwd(t_data *data, t_cmd *cmd)
{
	char	*cwd;
	int		fd;

	if (!cmd || !cmd->arg_list || !cmd->arg_list->value)
		return (1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror(cmd->arg_list->value), 1);
	fd = ft_get_fd_out(data, cmd);
	ft_putstr_fd(cwd, fd);
	ft_putstr_fd("\n", fd);
	free(cwd);
	if (fd != STDOUT_FILENO)
		close(fd);
	return (0);
}
