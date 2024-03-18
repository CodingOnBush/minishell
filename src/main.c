/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:03 by momrane           #+#    #+#             */
/*   Updated: 2024/03/18 22:38:16 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	t_data	data;

	printf("Welcome to minispell \\o_o/\n");
	ft_setup_signals(&data);// to handle ctrl + c (SIGINT) and ctrl + \ (SIGQUIT)
	while (1)
	{
		data.line = readline(PS1);
		if (!data.line)// it means that the user pressed ctrl + d (EOF)
		{
			free(data.line);
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
	return (0);
}
