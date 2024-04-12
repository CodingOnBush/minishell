/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:38:00 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/12 14:14:52 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_token	*ft_get_next_pipe_token(t_token *cur_token)
{
	if (cur_token == NULL)
		return (NULL);
	while (cur_token != NULL)
	{
		if (cur_token->type == PIPE)
			return (cur_token);
		cur_token = cur_token->next;
	}
	return (NULL);
}

static t_cmd	*ft_create_cmd_list(t_data *data, t_token *token_list)
{
	t_token	*cur_token;
	t_cmd	*cmd_list;
	t_cmd	*new_cmd;
	int		pos;

	cmd_list = NULL;
	cur_token = token_list;
	pos = 0;
	while (cur_token != NULL)
	{
		if (cur_token->type != PIPE)
		{
			new_cmd = ft_new_cmd(data, cur_token, pos);
			if (!new_cmd)
				return (printf("HO\n"), NULL);
			ft_add_new_cmd(&cmd_list, new_cmd);
			cur_token = ft_get_next_pipe_token(cur_token);
		}
		if (cur_token != NULL)
			cur_token = cur_token->next;
		pos++;
	}
	return (cmd_list);
}

int	ft_get_cmd_nb(t_cmd *cmd_list)
{
	t_cmd	*cur;
	int		cmd_nb;

	cmd_nb = 0;
	cur = cmd_list;
	while (cur != NULL)
	{
		cmd_nb++;
		cur = cur->next;
	}
	return (cmd_nb);
}

int	ft_parser(t_data *data)
{
	data->cmd_list = ft_create_cmd_list(data, data->token_list);
	if (!data->cmd_list)
		return (FAIL);
	data->cmd_nb = ft_get_cmd_nb(data->cmd_list);
	return (SUCCESS);
}
