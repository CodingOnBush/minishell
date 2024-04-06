/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:30:56 by momrane           #+#    #+#             */
/*   Updated: 2024/04/06 14:37:00 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data	*ft_create_data(int ac, char **av, char **env)
{
	t_data	*data;

	(void)ac;
	(void)av;
	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	ft_memset(data, 0, sizeof(t_data));
	data->line = NULL;
	data->env = env;
	data->cmd_list = NULL;
	data->token_list = NULL;
	data->cmd_nb = 0;
	data->hdnum = 0;
	data->fd_hd = NULL;
	data->hd_files = NULL;
	data->ids = NULL;
	data->pipe_ends = NULL;
	data->path_list = ft_split(getenv("PATH"), ':');
	data->join_path = NULL;
	data->step = 0;
	ft_setup_signals(data);
	return (data);
}

int	ft_finish_init_data(t_data *data)
{
	if (ft_check_quote_error(data->line) == FAIL)
		return (ft_print_error(QUOTES_ERROR), FAIL);
	data->token_list = ft_create_token_list(data->line);
	if (!data->token_list)
		return (FAIL);
	ft_start_expansion(&data->token_list);
	if (ft_double_pipe_detected(data->token_list) == YES)
		return (ft_print_error(DOUBLE_PIPE_ERROR), ft_free_all(data), FAIL);
	if (check_token_list(data->token_list) == FAIL)
		return (ft_free_all(data), FAIL);
	data->cmd_list = ft_create_cmd_list(data->token_list);
	if (!data->cmd_list)
		return (FAIL);
	data->cmd_nb = get_cmd_nb(data->cmd_list);
	return (SUCCESS);
}
