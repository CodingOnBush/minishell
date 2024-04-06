/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/06 15:34:12 by momrane           #+#    #+#             */
/*   Updated: 2024/04/06 18:39:32 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_get_cmd_path(char *cmd)
{
	return (ft_strdup(cmd));
}

static int	ft_init_new_cmd(t_cmd *new_cmd, t_token *cur_token)
{
	new_cmd->token_list = ft_extract_token(cur_token);
	if (!new_cmd->token_list)
		return (FAIL);
	new_cmd->arg_list = ft_create_arg_list(cur_token);
	if (!new_cmd->arg_list)
		return (FAIL);
	new_cmd->infile_list = ft_create_infile_list(cur_token);
	if (!new_cmd->infile_list)
		return (FAIL);
	new_cmd->outfile_list = ft_create_outfile_list(cur_token);
	if (!new_cmd->outfile_list)
		return (FAIL);
	new_cmd->args = ft_create_args_array(new_cmd->arg_list);
	if (!new_cmd->args)
		return (FAIL);
	new_cmd->cmd_path = ft_get_cmd_path(new_cmd->args[0]);
	if (!new_cmd->cmd_path)
		return (FAIL);
	new_cmd->next = NULL;
	return (SUCCESS);
}

t_cmd	*ft_new_cmd(t_token *cur_token, int pos)
{
	t_cmd	*new_cmd;

	if (cur_token == NULL)
		return (NULL);
	new_cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_cmd)
		return (NULL);
	ft_memset(new_cmd, 0, sizeof(t_cmd));
	new_cmd->pos = pos;
	if (ft_init_new_cmd(new_cmd, cur_token) == FAIL)
		return (ft_free_cmd(new_cmd), NULL);
	return (new_cmd);
}
