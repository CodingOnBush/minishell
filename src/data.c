/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:30:56 by momrane           #+#    #+#             */
/*   Updated: 2024/04/03 23:07:09 by momrane          ###   ########.fr       */
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
	data->hdnum = 0;
	data->cmd_nb = 0;
	data->ids = NULL;
	data->pipe_ends = NULL;
	ft_setup_signals(data);
	data->path_list = ft_split(getenv("PATH"), ':');
	data->step = 0;
	return (data);
}

int	ft_finish_init_data(t_data *data)
{
	if (ft_check_quote_error(data->line) == FAIL)
		return (ft_error_messages(QUOTES_ERROR), FAIL);
	data->token_list = ft_create_token_list(data->line);
	if (!data->token_list)
		return (printf("parse tokens failed !\n"), FAIL);
	ft_expand(&data->token_list);
	// ft_print_token_list(data->token_list);
	if (ft_check_double_pipe(data->token_list) == FAIL)
		return (ft_error_messages(DOUBLE_PIPE_ERROR), ft_free_all(data), FAIL);
	if (check_token_list(&data->token_list) == FAIL)
		return (ft_free_all(data), FAIL);
	data->cmd_list = ft_create_cmd_list(data->token_list);
	if (!data->cmd_list)
		return (FAIL);
	// ft_print_cmd_list(data->cmd_list);
	return (SUCCESS);
}
