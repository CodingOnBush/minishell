/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:38:01 by momrane           #+#    #+#             */
/*   Updated: 2024/03/27 17:39:53 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_start_exec(t_data *data)
{
	char	*res;

	printf("lets go exec !\n");
	printf("var : %s\n", data->cmd_list->token_list->str);
	res = getenv(data->cmd_list->token_list->str);
	printf("res : %s\n", res);
	printf("path[0] : %s\n", data->path_list[0]);
}
