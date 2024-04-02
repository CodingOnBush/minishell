/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:30:56 by momrane           #+#    #+#             */
/*   Updated: 2024/04/02 17:06:26 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data	*ft_create_data(int ac, char **av, char **env)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	(void)ac;
	(void)av;
	data->line = NULL;
	data->env = env;
	data->cmd_list = NULL;
	data->token_list = NULL;
	data->fd_hd = NULL;
	data->hd_files = NULL;
	ft_setup_signals(data);
	data->path_list = ft_split(getenv("PATH"), ':');
	data->step = 0;
	return (data);
}

static int	is_error_to_print(t_token *list)
{
	t_token	*cur_token;

	cur_token = list;
	while (cur_token != NULL)
	{
		if (cur_token->error == true)
		{
			ft_error_messages(cur_token->err_type);
			return (YES);
		}
		cur_token = cur_token->next;
	}
	return (NO);
}

int	ft_finish_init_data(t_data *data)
{
	if (ft_check_quote_error(data->line) == FAIL)
		return (ft_error_messages(QUOTES_ERROR), FAIL);
	data->token_list = ft_create_token_list(data->line);
	if (!data->token_list)
		return (printf("parse tokens failed !\n"), FAIL);
	ft_expand(data);
	ft_print_token_list(data->token_list);
	// if (ft_check_double_pipe(data->token_list) == FAIL)
	// 	return (ft_error_messages(DOUBLE_PIPE_ERROR), ft_free_tokens(&data->token_list), FAIL);
	// if (check_token_list(&data->token_list) == FAIL)
	// 	return (ft_free_tokens(&data->token_list), FAIL);
	// data->cmd_list = ft_create_cmd_list(data->token_list);
	// if (!data->cmd_list)
	// 	return (FAIL);
	// ft_print_token_list(data->token_list);
	// if (do_heredocs(data) == FAIL)
	// {
	// 	if (is_error_to_print(data->token_list) == NO)
	// 		pipe_at_end_error_check(data->token_list);
	// 	return (FAIL);
	// }
	// if (pipe_at_end_error_check(data->token_list) == FAIL)
	// 	return (FAIL);
	// if (is_error_to_print(data->token_list) == YES)
	// 	return (FAIL);
	return (SUCCESS);
}
