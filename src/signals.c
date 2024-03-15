/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:45:26 by momrane           #+#    #+#             */
/*   Updated: 2024/03/15 12:53:09 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_handler(int signum, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	printf("a signal has been caught : %d\n", signum);
}

void	ft_init_sigaction(t_data *data)
{
	data->action.sa_handler = ft_handler;
	data->action.sa_flags = SA_SIGINFO;
	sigemptyset(&data->action.sa_mask);
	sigaction(SIGINT, &data->action, NULL);
}
