/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:38:00 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/20 15:20:21 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_add_new_cmd(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	**tmp;

	if (*cmd_list == NULL)
	{
		*cmd_list = new_cmd;
		
	}
	else
	{
		tmp = cmd_list;
		while ((*tmp)->next != NULL)
			*tmp = (*tmp)->next;
		(*tmp)->next = new_cmd;
	}
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

static t_cmd	*ft_create_new_cmd(void)
{
	t_cmd	*new_cmd;
	
	new_cmd = malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->arg_list = NULL;
	new_cmd->infile_list = NULL;
	new_cmd->outfile_list = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}

t_token	*ft_get_last_redir(t_token *cur_token)
{
	while (cur_token && cur_token->type != PIPE)
	{
		if (cur_token->type == RIGHT_TRUNC || cur_token->type == LEFT_TRUNC)
			return (cur_token);
		cur_token = cur_token->next;
	}
	return (NULL);
}

t_cmd	*ft_create_cmd(t_token *cur_token)
{
	t_cmd	*new_cmd;

	if (cur_token == NULL)
		return (NULL);
	new_cmd = ft_create_new_cmd();
	if (!new_cmd)
		return (NULL);
	while (cur_token != NULL && cur_token->type != PIPE)
	{
		if (cur_token->type == HERE_DOC && cur_token->next != NULL && cur_token->next->type == WORD)
			new_cmd->delimiter = cur_token->next->value;
		cur_token = cur_token->next;
	}
	return (new_cmd);
}

t_cmd	*ft_create_cmd_list(t_token *token_list)
{
	t_token	*cur_token;
	t_cmd	*cmd_list;
	t_cmd	*new_cmd;

	cmd_list = NULL;
	cur_token = token_list;
	while (cur_token != NULL)
	{
		if (cur_token->type != PIPE)
		{
			new_cmd = ft_create_cmd(cur_token);
			if (!new_cmd)
				return (NULL);
			ft_add_new_cmd(&cmd_list, new_cmd);
			cur_token = ft_find_next_pipe(cur_token);
			if (!cur_token)
				return (cmd_list);
		}
		cur_token = cur_token->next;
	}
	return (cmd_list);
}

// t_cmd	*ft_create_cmd_list(t_token *token_list)
// {
// 	t_token	*cur_token;
// 	t_cmd	*cmd_list;
// 	t_cmd	*new_cmd;
// 	t_cmd	*tmp;
// 	t_token	*nxt_redir;

// 	cmd_list = NULL;
// 	cur_token = token_list;
// 	while (cur_token != NULL)
// 	{
// 		new_cmd = ft_create_new_cmd();
// 		if (!new_cmd)
// 			return (NULL);		
		
// 		while (cur_token != NULL && cur_token->type != PIPE)
// 		{
// 			if (cur_token->type == HERE_DOC && cur_token->next != NULL)
// 				new_cmd->delimiter = cur_token->next->value;
// 			nxt_redir = ft_get_last_redir(cur_token);
// 			if (nxt_redir != NULL && nxt_redir->next != NULL && nxt_redir->next->type == WORD)
// 			{
// 				if (nxt_redir->type == RIGHT_TRUNC)
// 				{
// 					// add new outfile_list
// 					new_cmd->outfile_list->filename = nxt_redir->next->value;
// 					new_cmd->outfile_list->append = false;
// 					// new_cmd->outfile_list->next
// 				}
// 			}
// 			cur_token = cur_token->next;
// 		}
		


// 		if (cmd_list == NULL)
// 			cmd_list = new_cmd;
// 		else
// 		{
// 			tmp = cmd_list;
// 			while (tmp->next != NULL)
// 				tmp = tmp->next;
// 			tmp->next = new_cmd;
// 		}
// 	}
// 	return (cmd_list);
// }
