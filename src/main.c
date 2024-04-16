/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:41:37 by momrane           #+#    #+#             */
/*   Updated: 2024/04/16 09:22:12 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int g_signum = 0;

int	main(int ac, char **av, char **env)
{
	t_data *const	data = ft_create_data(env);
	int				status;

	(void)ac;
	(void)av;
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
		if (data->cmd_nb > 1 && is_exit_builtin(data) == YES)
		{
			ft_free_all(data);
			exit(0);
		}
		ft_reset_data(data);
	}
	status = data->exit_status;
	ft_free_all(data);
	// rl_clear_history();
	printf("exit\n");
	return (status);
}
