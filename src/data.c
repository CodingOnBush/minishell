/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:30:56 by momrane           #+#    #+#             */
/*   Updated: 2024/03/27 17:46:14 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_data	*ft_create_data(void)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->line = NULL;
	data->cmd_list = NULL;
	data->token_list = NULL;
	ft_setup_signals(data);
	data->path_list = ft_split(getenv("PATH"), ':');
	return (data);
}

int	ft_finish_init_data(t_data *data)
{
	if (ft_check_quote_error(data->line) == FAIL)
		return (ft_error_messages(QUOTES_ERROR), FAIL);
	data->token_list = ft_create_token_list(data->line);
	if (!data->token_list)
		return (printf("parse tokens failed !\n"), FAIL);
	if (ft_check_double_pipe(data->token_list) == FAIL)
	{
		ft_error_messages(DOUBLE_PIPE_ERROR);
		return (ft_free_tokens(&data->token_list), FAIL);
	}
	if (check_token_list(&data->token_list) == FAIL)
		return (ft_free_tokens(&data->token_list), FAIL);
	data->cmd_list = ft_create_cmd_list(data->token_list);
	if (!data->cmd_list)
		return (FAIL);
	return (SUCCESS);
}
