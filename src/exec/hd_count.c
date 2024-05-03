/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hd_count.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/29 18:14:26 by vvaudain          #+#    #+#             */
/*   Updated: 2024/05/02 12:22:11 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_get_err_pos(t_cmd *cmd)
{
	t_token	*cur_token;
	int		err_pos;

	err_pos = -1;
	cur_token = cmd->token_list;
	while (cur_token != NULL)
	{
		if (cur_token->error == true)
		{
			err_pos = cur_token->pos;
			return (err_pos);
		}
		else if (cur_token->pipe_at_end == true)
			return (cur_token->next->pos);
		cur_token = cur_token->next;
	}
	return (err_pos);
}

static int	ft_hd_count_pre_err(t_cmd *cmd)
{
	t_token	*cur;
	int		err_pos;
	int		hd_count;

	if (cmd == NULL)
		return (0);
	err_pos = 0;
	hd_count = 0;
	err_pos = ft_get_err_pos(cmd);
	cur = cmd->token_list;
	while (cur != NULL && cur->pos < err_pos)
	{
		if (cur->type == HD && cur->next != NULL && cur->next->type == LIM
			&& cur->error == false && cur->next->error == false)
			hd_count++;
		cur = cur->next;
	}
	if (cur != NULL && cur->pos == err_pos && cur->pipe_at_end == true)
		hd_count++;
	return (hd_count);
}

static int	ft_count_hd(t_token *list)
{
	t_token	*cur;
	int		hd_count;

	if (list == NULL)
		return (0);
	cur = list;
	hd_count = 0;
	while (cur != NULL)
	{
		if (cur->type == HD && cur->next != NULL && cur->next->type == LIM
			&& cur->error == false && cur->next->error == false)
			hd_count++;
		cur = cur->next;
	}
	return (hd_count);
}

int	ft_get_hd_nb(t_cmd *list)
{
	int		hdnum;
	t_cmd	*cur_cmd;
	t_token	*cur_tk;

	hdnum = 0;
	cur_cmd = list;
	while (cur_cmd != NULL)
	{
		cur_tk = cur_cmd->token_list;
		while (cur_tk != NULL)
		{
			if (cur_tk->error == true || cur_tk->pipe_at_end == true)
				break ;
			cur_tk = cur_tk->next;
		}
		if (cur_tk != NULL && (cur_tk->error == true
				|| cur_tk->pipe_at_end == true))
			break ;
		hdnum += ft_count_hd(cur_cmd->token_list);
		cur_cmd = cur_cmd->next;
	}
	if (cur_cmd != NULL && (cur_tk->error == true
			|| cur_tk->pipe_at_end == true))
		hdnum += ft_hd_count_pre_err(cur_cmd);
	return (hdnum);
}
