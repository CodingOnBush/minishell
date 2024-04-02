/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 17:41:37 by momrane           #+#    #+#             */
/*   Updated: 2024/04/02 14:51:26 by vvaudain         ###   ########.fr       */
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
		data->line = readline("minishell > ");
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