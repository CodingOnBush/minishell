/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:03 by momrane           #+#    #+#             */
/*   Updated: 2024/03/21 11:11:07 by vvaudain         ###   ########.fr       */
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
		printf("============\ncmd %d\n", i);
		// printf("cmds->args : %p\n", cmds->arg_list);
		printf("delimiter : %s\n", cmds->delimiter);
		printf("infile : %s\n", cmds->infile_list->filename);
		printf("outfile : %s\n", cmds->outfile_list->filename);
		// while (cmds->arg_list)
		// {
		// 	printf("arg %d : %s\n", j, cmds->arg_list->value);
		// 	j++;
		// 	cmds->arg_list = cmds->arg_list->next;
		// }
		i++;
		cmds = cmds->next;
	}
}

int	main(int ac, char **av, char **env)
{
	t_data	data;

	printf("Welcome to minispell \\o_o/\n");
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
		// print_list(data.token_list);
		
		// create cmd list
		data.cmd_list = ft_create_cmd_list(data.token_list);
		if (!data.cmd_list)
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
