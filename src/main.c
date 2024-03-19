/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:03 by momrane           #+#    #+#             */
/*   Updated: 2024/03/19 13:55:11 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	data;

	printf("Welcome to minispell \\o_o/\n");
	(void)ac;
	(void)av;
	(void)env;
	ft_setup_signals(&data);// to handle ctrl + c (SIGINT) and ctrl + \ (SIGQUIT)
	data.ac = ac;
	data.av = av;
	data.env = env;
	data.path = NULL;
	ft_set_path(&data);
	while (1)
	{
		data.line = readline(MINISPELL);
		if (!data.line)// it means that the user pressed ctrl + d (EOF)
		{
			printf("exit\n");
			break ;
		}
		data.token_list = ft_create_token_list(data.line);
		if (data.token_list)
			print_list(data.token_list);
		else
			printf("no token list\n");
		free(data.line);
		ft_free_tokens(&data.token_list);
	}
	ft_free_path(data.path);
	return (0);
}
