/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:39:05 by allblue           #+#    #+#             */
/*   Updated: 2024/04/12 13:44:43 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_init_new_cmd(t_data *data, t_cmd *new_cmd, t_token *cur_token)
{
	new_cmd->token_list = ft_extract_token(cur_token);
	if (!new_cmd->token_list)
		return (FAIL);
	new_cmd->infile_list = ft_create_infile_list(data, new_cmd->token_list);
	new_cmd->outfile_list = ft_create_outfile_list(new_cmd->token_list);
	new_cmd->arg_list = ft_create_arg_list(new_cmd->token_list);
	// if (!new_cmd->arg_list)
	// 	return (FAIL);
	new_cmd->args = ft_create_args_array(new_cmd->arg_list);
	new_cmd->cmd_path = NULL;
	new_cmd->next = NULL;
	return (SUCCESS);
}

t_cmd	*ft_new_cmd(t_data *data, t_token *cur_token, int pos)
{
	t_cmd	*new_cmd;
	t_token	*next_token;

	if (!cur_token)
		return (NULL);
	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	ft_memset(new_cmd, 0, sizeof(t_cmd));
	new_cmd->pos = pos;
	if (cur_token->next)
		next_token = cur_token->next;
	else
		next_token = NULL;
	if (ft_init_new_cmd(data, new_cmd, cur_token) == FAIL)
		return (ft_free_cmd(new_cmd), NULL);
	return (new_cmd);
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
