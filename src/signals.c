/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 12:45:26 by momrane           #+#    #+#             */
/*   Updated: 2024/03/23 16:23:41 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_handler(int signum)
{
	if (signum == SIGINT)
	{
		printf("\n");
		// rl_replace_line("", STDIN_FILENO);// "ls |\n>"
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	ft_setup_sigint(t_data *data)
{
	data->sigint_action.sa_handler = ft_handler;
	sigemptyset(&data->sigint_action.sa_mask);
	data->sigint_action.sa_flags = 0;//to have a ft_handler with only one arg (signum)
	sigaction(SIGINT, &data->sigint_action, NULL);
}

static void	ft_setup_sigquit(t_data *data)
{
	data->sigquit_action.sa_handler = SIG_IGN;
	sigemptyset(&data->sigquit_action.sa_mask);
	data->sigquit_action.sa_flags = 0;
	sigaction(SIGQUIT, &data->sigquit_action, NULL);
}

void	ft_setup_signals(t_data *data)
{
	ft_setup_sigint(data);
	ft_setup_sigquit(data);
}
