/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:03 by momrane           #+#    #+#             */
/*   Updated: 2024/03/14 15:29:27 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(void)
{
	t_data	data;

	printf("Welcome to minispell \\o_o/\n");
	while (1)
	{
		data.line = readline("minispell > ");
		if (!data.line)
			break ;
		data.token_list = ft_create_token_list(data.line);
		if (data.token_list)
			print_list(data.token_list);
		else
			printf("no token list\n");
		free(data.line);
	}
	return (0);
}
