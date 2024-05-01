/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:38:00 by vvaudain          #+#    #+#             */
/*   Updated: 2024/05/01 16:38:50 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_cmd	*ft_new_cmd(t_data *data, t_token *cur_token, int pos)
{
	t_cmd	*new_cmd;

	if (!cur_token)
		return (NULL);
	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	ft_memset(new_cmd, 0, sizeof(t_cmd));
	new_cmd->pos = pos;
	new_cmd->token_list = ft_extract_token(cur_token);
	new_cmd->infile_list = ft_create_infile_list(data, new_cmd->token_list);
	new_cmd->outfile_list = ft_create_outfile_list(new_cmd->token_list);
	new_cmd->arg_list = ft_create_arg_list(new_cmd->token_list);
	new_cmd->args = ft_create_args_array(new_cmd->arg_list);
	new_cmd->cmd_path = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

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

static void	ft_add_new_cmd(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	*tmp;

	if (*cmd_list == NULL)
		*cmd_list = new_cmd;
	else
	{
		tmp = *cmd_list;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_cmd;
	}
}

int	ft_parser(t_data *data)
{
	t_token	*cur;
	t_cmd	*new;

	cur = data->token_list;
	data->cmd_list = NULL;
	data->cmd_nb = 0;
	while (cur != NULL)
	{
		if (cur->type != PIPE)
		{
			new = ft_new_cmd(data, cur, data->cmd_nb);
			if (!new)
				return (ft_free_cmd_list(&data->cmd_list), FAIL);
			data->cmd_nb++;
			ft_add_new_cmd(&data->cmd_list, new);
			cur = ft_get_next_pipe_token(cur);
			if (!cur)
				break ;
		}
		cur = cur->next;
	}
	return (SUCCESS);
}
