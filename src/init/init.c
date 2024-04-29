/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:30:56 by momrane           #+#    #+#             */
/*   Updated: 2024/04/29 14:39:12 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signum = signum;
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", STDIN_FILENO);
		rl_on_new_line();
		rl_redisplay();
	}
}

static void	ft_setup_signals(t_data *data)
{
	data->act_interupt.sa_handler = ft_handler;
	data->act_quit.sa_handler = SIG_IGN;
	sigemptyset(&data->act_interupt.sa_mask);
	sigemptyset(&data->act_quit.sa_mask);
	data->act_interupt.sa_flags = 0;
	data->act_quit.sa_flags = 0;
	sigaction(SIGINT, &data->act_interupt, NULL);
	sigaction(SIGQUIT, &data->act_quit, NULL);
}

t_data	*ft_create_data(int ac, char **av, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	(void)ac;
	(void)av;
	if (!data)
		return (NULL);
	ft_memset(data, 0, sizeof(t_data));
	data->line = NULL;
	data->cmd_list = NULL;
	data->token_list = NULL;
	data->cmd_nb = 0;
	data->hdnum = 0;
	data->fd_hd = NULL;
	data->hd_files = NULL;
	data->ids = NULL;
	data->pipe_ends = NULL;
	data->join_path = NULL;
	data->step = 0;
	data->env_list = ft_create_envlist(env);
	data->exp_list = ft_create_envlist(env);
	data->hd_pos = -1;
	data->exit_status = 0;
	data->exit_builtin = NO;
	ft_setup_signals(data);
	return (data);
}
