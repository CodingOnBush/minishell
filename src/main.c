/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:03 by momrane           #+#    #+#             */
/*   Updated: 2024/03/21 12:58:26 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

/* ls << EOF cat << EOF hey > file1 > fiel2 > ls >> file3 */

static t_data	*ft_create_data(int ac, char **av, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	ft_setup_signals(data);
	data->ac = ac;
	data->av = av;
	data->env = env;
	data->path = NULL;
	data->cmd_list = NULL;
	ft_set_path(data);
	return (data);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	printf("Welcome to minispell \\o_o/\n");
	data = ft_create_data(ac, av, env);
	if (!data)
		return (-1);
	while (1)
	{
		data->line = readline(MINISPELL);
		if (!data->line)
		{
			printf("exit\n");
			break ;
		}
		
		// create token list
		data->token_list = ft_create_token_list(data->line);
		if (!data->token_list)
		{
			printf("no token list\n");
			break;
		}
		
		// create cmd list
		data->cmd_list = ft_create_cmd_list(data->token_list);
		if (!data->cmd_list)
		{
			printf("parse commands failed !\n");
			break;
		}
		printf("HEY\n");
	
		free(data->line);
		ft_free_tokens(&data->token_list);
	}
	ft_free_path(data->path);
	return (0);
}
