/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:03 by momrane           #+#    #+#             */
/*   Updated: 2024/03/20 13:05:06 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	print_args(t_cmd *cmds)
{
	int	i;
	int	j;

	if (cmds == NULL)
	{
		printf("args empty\n");
		return ;
	}
	i = 0;
	j = 0;
	while (cmds)
	{
		printf("cmd %d\n", i);
		printf("cmds->args : %p\n", cmds->words);
		while (cmds->words)
		{
			printf("arg %d : %s\n", j, cmds->words->value);
			j++;
			cmds->words = cmds->words->next;
		}
		i++;
		cmds = cmds->next;
	}
}

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
	data.cmd_list = NULL;
	ft_set_path(&data);
	while (1)
	{
		data.line = readline(MINISPELL);
		if (!data.line)// it means that the user pressed ctrl + d (EOF)
		{
			printf("exit\n");
			break ;
		}
		
		// create token list
		data.token_list = ft_create_token_list(data.line);
		if (!data.token_list)
		{
			printf("no token list\n");
			break;
		}
		print_list(data.token_list);
		
		// create cmd list
		data.cmd_list = ft_create_cmd_list(data.token_list);
		if (data.cmd_list)
		{
			printf("parse commands failed !\n");
			break;
		}
		print_args(data.cmd_list);
	
		free(data.line);
		ft_free_tokens(&data.token_list);
	}
	ft_free_path(data.path);
	return (0);
}
