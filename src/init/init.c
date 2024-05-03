/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:30:56 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 11:24:30 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_handle_no_double_prompt(int signum)
{
	if (signum == SIGINT)
	{
		g_signum = signum;
		rl_on_new_line();
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", STDIN_FILENO);
	}
	if (signum == SIGQUIT)
	{
		g_signum = signum;
		ft_putstr_fd("Quit: (core dumped)\n", STDOUT_FILENO);
	}
}

t_data	*ft_create_data(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_data));
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
	data->exp_list = ft_create_explist(env);
	data->hd_pos = -1;
	data->exit_status = 0;
	data->exit_builtin = NO;
	return (data);
}
