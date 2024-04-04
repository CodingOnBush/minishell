/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:41:37 by momrane           #+#    #+#             */
/*   Updated: 2024/04/04 16:39:09 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	wait_for_children(t_data *data)
{
	int	status;
	int	i;

	i = 0;
	if (!data || data->cmd_nb == 0)
		return ;
	while (i < data->cmd_nb)
	{
		waitpid(data->ids[i], &status, 0);
		printf("status = %d\n", status);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data *const	data = ft_create_data(ac, av, env);

	if (!data)
		return (-1);
	while (1)
	{
		data->line = readline(MINISPELL);
		if (!data->line)
			break ;
		add_history(data->line);
		if (ft_finish_init_data(data) == SUCCESS)
			ft_start_exec(data);
		wait_for_children(data);
		ft_free_lexing_and_parsing(data);
		ft_free_exec(data);
		unlink_and_free(data);
		free(data->line);
	}
	ft_free_all(data);
	rl_clear_history();
	printf("exit\n");
	return (0);
}

// char	*args[4];
// (void)ac;
// (void)av;
// args[0] = "ls";
// args[1] = "-la";
// args[2] = "cat";
// args[3] = "infile";
// if (execve("/usr/bin/ls", args, env) == 0)
// 	printf("errorrrr\n");