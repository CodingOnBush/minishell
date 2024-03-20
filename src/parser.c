/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:38:00 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/20 11:43:55 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_parse_commands(t_data *data)
{
	t_token	*cur_token;
	t_cmd	*new_cmd;

	cur_token = data->token_list;
	while (cur_token != NULL)
	{
		new_cmd = malloc(sizeof(t_cmd));
		if (!new_cmd)
			return (FAIL);
		new_cmd->next = NULL;
		new_cmd->args = NULL;
		while (cur_token != NULL && *cur_token->value != '|')
		{
			if (cur_token->type == WORD && !cur_token->next)
			{
				if (add_new_arg(new_cmd->args, cur_token->value) == FAIL)
					return (FAIL);
			}
			cur_token = cur_token->next;
		}
		if (data->cmd_list == NULL)
			data->cmd_list = new_cmd;
		else
		{
			while (data->cmd_list->next)
				data->cmd_list = data->cmd_list->next;
			data->cmd_list->next = new_cmd;
		}
	}
	return (SUCCESS);
}
