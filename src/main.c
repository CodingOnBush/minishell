/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:41:37 by momrane           #+#    #+#             */
/*   Updated: 2024/04/03 13:11:33 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
		unlink_and_free(data, data->hd_files);
		//supprimer les fichiers des hd dans l'exec a la fin ou bien la
		ft_free_lexing_and_parsing(data);
		free(data->line);
	}
	ft_free_path(data->path_list);
	rl_clear_history();
	printf("exit\n");
	return (free(data), 0);
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