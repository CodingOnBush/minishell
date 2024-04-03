/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:53:11 by momrane           #+#    #+#             */
/*   Updated: 2024/04/03 17:59:31 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_cmd	*ft_create_cmd(t_token *cur_token, int pos)
{
	t_cmd	*new_cmd;

	if (cur_token == NULL)
		return (NULL);
	new_cmd = ft_create_new_cmd(cur_token, pos);
	if (!new_cmd)
		return (NULL);
	parse_infiles(new_cmd, cur_token);
	parse_outfiles(new_cmd, cur_token);
	parse_commands(new_cmd, cur_token);
	return (new_cmd);
}

t_cmd	*ft_create_cmd_list(t_token *token_list)
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
			new_cmd = ft_create_cmd(cur_token, pos);
			if (!new_cmd)
				return (ft_free_cmds(&cmd_list), NULL);
			ft_add_new_cmd(&cmd_list, new_cmd);
			cur_token = ft_find_next_pipe(cur_token);
			if (cur_token == NULL)
				return (cmd_list);
		}
		cur_token = cur_token->next;
		pos++;
	}
	return (cmd_list);
}

void	ft_add_new_cmd(t_cmd **cmd_list, t_cmd *new_cmd)
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

t_cmd	*ft_create_new_cmd(t_token *cur_token, int pos)
{
	t_cmd	*new_cmd;
	
	if (!cur_token)
		return (NULL);
	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	new_cmd->token_list = ft_extract_token(cur_token);
	if (!new_cmd->token_list)
		return (free(new_cmd), NULL);
	new_cmd->arg_list = NULL;
	new_cmd->pos = pos;
	new_cmd->infile_list = NULL;
	new_cmd->outfile_list = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}
