/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:03 by momrane           #+#    #+#             */
/*   Updated: 2024/03/22 15:17:21 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	data->token_list = NULL;
	ft_set_path(data);
	return (data);
}

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

/* ls << EOF cat << EOF hey > file1 > fiel2 > ls >> file3 */


char	*find_path(t_data *data)
{
	t_arg	*arg_list;
	int		i;
	char	*big_cmd;

	arg_list = data->cmd_list->arg_list;
	if (arg_list == NULL)
		return (NULL);
	i = 0;
	data->cmd_list->arg_list->value = ft_strjoin("/", data->cmd_list->arg_list->value);
	if (!data->cmd_list->arg_list->value)
		return (NULL);
	while (data->path[i] != NULL)
	{
		big_cmd = ft_strjoin(data->path[i], arg_list->value);
		if (!big_cmd)
			return (NULL);
		if (access(big_cmd, F_OK) == 0)
			return (big_cmd);
		i++;
	}
	return (NULL);
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
		add_history(data->line);
		
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
		// if (do_heredocs(&data) == FAIL)
		// {
		// 	printf("A heredoc failed at some point !\n");
		// 	break;
		// }
		printf("cmd_path : %s\n", find_path(data));
	
		free(data->line);
		ft_free_tokens(&data->token_list);
	}
	rl_clear_history();
	ft_free_path(data->path);
	return (0);
}
