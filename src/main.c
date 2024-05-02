/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:32:05 by vvaudain          #+#    #+#             */
/*   Updated: 2024/05/02 09:34:13 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signum;

static void	ft_exitstatus_signal(t_data *data)
{
	if (g_signum != 0)
	{
		data->exit_status = g_signum + 128;
		g_signum = 0;
	}
}

static void	ft_wait_for_children(t_data *data)
{
	int	status;
	int	i;
	int	pid;

	if (!data->ids)
		ft_exitstatus_signal(data);
	else
	{
		status = 0;
		i = 0;
		while (i < data->cmd_nb)
		{
			pid = wait(&status);
			if (pid == data->ids[data->cmd_nb - 1])
			{
				data->exit_status = 0;
				if (WIFEXITED(status))
					data->exit_status = WEXITSTATUS(status);
				if (WIFSIGNALED(status))
					data->exit_status = WTERMSIG(status) + 128;
			}
			g_signum = 0;
			i++;
		}		
	}
}

static void	ft_standard_handler(int signum)
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

int	main(int ac, char **av, char **env)
{
	t_data *const	data = ft_create_data(ac, av, env);
	int				s;

	if (!data || ac != 1)
		return (-1);
	while (1)
	{
		signal(SIGINT, &ft_standard_handler);
		signal(SIGQUIT, SIG_IGN);
		data->line = readline(MINISPELL);
		if (!data->line)
			break ;
		ft_exitstatus_signal(data);
		if (data->line[0] != '\0')
			add_history(data->line);
		if (ft_lexer(data) == SUCCESS && ft_parser(data) == SUCCESS)
			ft_launch_exec(data);
		ft_wait_for_children(data);
		ft_reset_data(data);
	}
	if (isatty(STDIN_FILENO))
		write(2, "exit\n", 6);
	return (s = data->exit_status, rl_clear_history(), ft_free_all(data), s);
}
