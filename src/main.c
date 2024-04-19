/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/04/19 14:27:03 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../inc/minishell.h"

int g_signum = 0;

int	main(int ac, char **av, char **env)
{
	t_data *const	data = ft_create_data(ac, av, env);
	int				status;

	if (!data)
		return (-1);
	while (1)
	{
		data->line = readline(MINISPELL);
		if (!data->line)
			break ;
		add_history(data->line);
		if (ft_lexer(data) == SUCCESS && ft_parser(data) == SUCCESS)
			ft_launch_exec(data);
		ft_wait_for_children(data);
		if (is_exit_builtin(data) == YES)
		{
			status = data->exit_status;
			ft_free_all(data);
			exit(status);
		}
		ft_reset_data(data);
	}
	status = data->exit_status;
	rl_clear_history();
	return (ft_free_all(data), ft_putstr_fd("exit\n", 1), status);
}
