/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:53:11 by momrane           #+#    #+#             */
/*   Updated: 2024/04/06 15:34:31 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
	ft_memset(new_cmd, 0, sizeof(t_cmd));
	new_cmd->token_list = ft_extract_token(cur_token);
	if (!new_cmd->token_list)
		return (free(new_cmd), NULL);
	new_cmd->arg_list = NULL;
	new_cmd->infile_list = NULL;
	new_cmd->outfile_list = NULL;
	new_cmd->pos = pos;
	new_cmd->args = NULL;
	new_cmd->cmd_path = NULL;
	new_cmd->next = NULL;
	return (new_cmd);
}
