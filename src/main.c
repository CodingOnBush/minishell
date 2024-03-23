/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:03 by momrane           #+#    #+#             */
/*   Updated: 2024/03/23 17:38:07 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	data = ft_create_data(ac, av, env);
	if (!data)
		return (-1);
	ft_print_welcome_msg();
	while (1)
	{
		data->line = readline(MINISPELL);
		if (!data->line)
		{
			printf("exit\n");
			break ;
		}
		add_history(data->line);
		
		// create token list
		data->token_list = ft_create_token_list(data->line);
		ft_print_token_list(data->token_list);
		
		// create cmd list
		// data->cmd_list = ft_create_cmd_list(data->token_list);
		// if (!data->cmd_list)
		// {
		// 	printf("parse commands failed !\n");
		// 	ft_free_tokens(data->token_list);
		// 	free(data->line);
		// 	break;
		// }
		// printf("HEY\n");
		// if (do_heredocs(&data) == FAIL)
		// {
		// 	printf("A heredoc failed at some point !\n");
		// 	break;
		// }
		// printf("cmd_path : %s\n", // find_path(data));
	
		free(data->line);
		ft_free_tokens(&data->token_list);
	}
	// rl_clear_history();
	ft_free_path(data->path);
	free(data);
	return (0);
}

/*
===================
TEST ft_get_new_str
===================
int	main(void)
{
	char	*str;
	int		type;
	char	*line;

	line = ft_strdup("couc\"ou\"hey");
	if (!line)
		return (FAIL);
	printf("line : %s\n", line);
	type = ft_get_type(line);
	printf("type : %d(%s)\n", type, ft_type_to_str(type));
	str = ft_get_new_str(line, type);
	if (!str)
		return (FAIL);
	printf("str : %s\n", str);
	free(line);
	free(str);
	return (0);
}

*/

/*
char	*args[4];

(void)ac;
(void)av;
args[0] = "ls";
args[1] = "-la";
args[2] = "cat";
args[3] = "infile";

if (execve("/usr/bin/ls", args, env) == 0)
{
	printf("errorrrr\n");
}
*/