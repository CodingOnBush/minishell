/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 08:15:35 by momrane           #+#    #+#             */
/*   Updated: 2024/04/19 11:11:27 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_print_fdout(t_data *data, t_cmd *cmd, char *str)
{
	int	fd;

	fd = ft_get_fd_out(data, cmd);
	ft_putstr_fd(str, fd);
	close(fd);
}
