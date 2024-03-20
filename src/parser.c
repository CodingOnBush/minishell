/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:38:00 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/20 13:23:45 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_cmd	*create_new_cmd()
{
	t_cmd	*new_cmd;

	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);	
	new_cmd->words = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

int	ft_parse_commands(t_data *data)
{
	t_token	*cur_token;
	t_cmd	*cmd;

	cur_token = data->token_list;
	while (cur_token != NULL)
	{
		cmd = create_new_cmd();
		if (!cmd)
			return (FAIL);
		while (cur_token != NULL && cur_token->type != PIPE)
		{
			if (cur_token->type == WORD)
			{
				if (add_new_word(&cmd->words, cur_token->value) == FAIL)
					return (FAIL);
			}
			cur_token = cur_token->next;
		}
		if (data->cmd_list == NULL)
			data->cmd_list = cmd;
		else
		{
			while (data->cmd_list->next != NULL)
				data->cmd_list = data->cmd_list->next;
			data->cmd_list->next = cmd;
		}
	}
	return (SUCCESS);
}

static t_cmd	*ft_create_cmd(t_token *cur_token)
{
	if (cur_token == NULL)
		return (NULL);
	while (cur_token != NULL && cur_token->type != PIPE)
	{
		printf("loop\n");
		cur_token = cur_token->next;
	}
	return (NULL);
}

t_token	*ft_find_next_pipe(t_token *cur_token)
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

t_cmd	*ft_create_cmd_list(t_token *token_list)
{
	t_token	*cur_token;
	t_cmd	*cmd_list;
	t_cmd	*cmd_list2;
	t_cmd	*cmd;

	cur_token = token_list;
	cmd_list = NULL;
	while (cur_token != NULL)
	{
		if (cur_token->type != PIPE)
		{
			cmd = ft_create_cmd(cur_token);
			if (!cmd)
				return (NULL);
			cur_token = ft_find_next_pipe(cur_token);
			if (cur_token != NULL)
				cur_token = cur_token->next;
		}
		if (cmd_list == NULL)
			cmd_list = cmd;
		else
		{
			cmd_list2 = cmd_list;
			while (cmd_list2->next != NULL)
				cmd_list2 = cmd_list2->next;
			cmd_list2->next = cmd;
		}
	}
	return (cmd_list);
}
