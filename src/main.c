/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:03 by momrane           #+#    #+#             */
/*   Updated: 2024/03/22 18:10:44 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	main(int ac, char **av, char **env)
{
	t_data	*data;

	ft_welcome_msg("Welcome to minispell \\o_o/");
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
			// free(data->line);
			// break;
		}
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
	rl_clear_history();
	ft_free_path(data->path);
	free(data);
	return (0);
}

/*


echo ""$test""
echo "" $test ""
echo ""   $test   ""
echo ab"$test"
echo ab "$test"
echo ab   "$test"

echo "" bonjour
echo ""bonjour


```
bash-5.1$ export var="  truc"; echo $var
truc
bash-5.1$ var="  truc"
bash-5.1$ echo $var
truc
bash-5.1$ var="  trswqsuc"
bash-5.1$ echo $var
trswqsuc
bash-5.1$ var="                 trswqsuc"
bash-5.1$ echo $var
trswqsuc
bash-5.1$ var="q                 trswqsuc"
bash-5.1$ echo $var
q trswqsuc
```


export "test=ici"=coucou ; echo $test





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