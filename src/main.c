/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:03 by momrane           #+#    #+#             */
/*   Updated: 2024/03/21 17:23:53 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_data	*ft_create_data(int ac, char **av, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->ac = ac;
	data->av = av;
	data->env = env;
	data->path = NULL;
	data->line = NULL;
	data->cmd_list = NULL;
	data->token_list = NULL;
	ft_set_path(data);
	ft_setup_signals(data);
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
	while (data->path[i] != NULL)
	{
		big_cmd = ft_strjoin(data->path[i], arg_list->value);
		if (!big_cmd)
			return (NULL);
		// if (access(big_cmd, ))
		i++;
	}
	return (NULL);
}

void	ft_print_token_list(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	printf("TOKEN LIST\n");
	if (tmp == NULL)
	{
		printf("token list empty\n");
		return ;
	}
	printf("str\t\ttypecode\ttypename\tattributed\n");
	while (tmp)
	{
		printf("%s\t\t%d\t\t%s\t\t%d\n", tmp->str, tmp->type, ft_type_to_str(tmp->type), tmp->attributed);
		tmp = tmp->next;
	}
	printf("\n");
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
			free(data->line);
			break;
		}
		
		ft_print_token_list(data->token_list);

		// create cmd list
		// data->cmd_list = ft_create_cmd_list(data->token_list);
		// if (!data->cmd_list)
		// {
		// 	printf("parse commands failed !\n");
		// 	break;
		// }
		// printf("HEY\n");

		// find_path(data->cmd_list->arg_list);
	
		free(data->line);
		ft_free_tokens(&data->token_list);
	}
	ft_free_path(data->path);
	free(data);
	return (0);
}
