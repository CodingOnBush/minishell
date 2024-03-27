/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: Invalid date        by                   #+#    #+#             */
/*   Updated: 2024/03/27 14:54:23 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_start_lexing(t_data *data)
{
	if (ft_check_quote_error(data->line) == FAIL)
	{
		ft_error_messages(QUOTES_ERROR);
		return (FAIL);
	}
	data->token_list = ft_create_token_list(data->line);
	if (!data->token_list)
	{
		printf("parse tokens failed !\n");
		return (FAIL);
	}
	if (ft_check_double_pipe(data->token_list) == FAIL)
	{
		ft_error_messages(DOUBLE_PIPE_ERROR);
		return (FAIL);
	}
	if (check_token_list(&data->token_list) == FAIL)
		return (FAIL);
	return (SUCCESS);
}
int	ft_start_parsing(t_data *data)
{
	data->cmd_list = ft_create_cmd_list(data->token_list);
	if (!data->cmd_list)
	{
		printf("parse commands failed !\n");
		return (FAIL);
	}
	ft_print_cmd_list(data->cmd_list);
	return (SUCCESS);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;

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
		// add_history(data->line);// leaks from this function
		if (ft_start_lexing(data) == FAIL)
		{
			free(data->line);
			continue;
		}
		if (ft_start_parsing(data) == FAIL)
		{
			free(data->line);
			ft_free_tokens(&data->token_list);
			continue;
		}
		ft_free_cmds(&data->cmd_list);
		free(data->line);
	}
	ft_free_path(data->path);
	free(data);
	return (0);
}

// int	main(int ac, char **av, char **env)
// {
// 	t_data	*data;

// 	data = ft_create_data(ac, av, env);
// 	if (!data)
// 		return (-1);
	
// 	data->line = ft_strdup("cat Mae | grep pr | head -n 5 | cd fil");
	
// 	data->token_list = ft_create_token_list(data->line);
// 	if (!data->token_list)
// 		return (printf("parse tokens failed !\n"));
	
// 	data->cmd_list = ft_create_cmd_list(data->token_list);
// 	if (!data->cmd_list)
// 		return (printf("parse commands failed !\n"));
	
// 	printf("%s\n", data->line);
// 	ft_print_cmd_list(data->cmd_list);
// }

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