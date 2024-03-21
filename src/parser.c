/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:38:00 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/21 14:45:59 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_add_new_cmd(t_cmd **cmd_list, t_cmd *new_cmd)
{
	t_cmd	**tmp;

	if (*cmd_list == NULL)
		*cmd_list = new_cmd;
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

static int	parse_infiles(t_cmd *new_cmd, t_token *token)
{
	t_infile	*new_infile;

	new_infile = NULL;
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == LEFT_TRUNC || token->type == HERE_DOC)
		{
			if (token->next == NULL)
				return (ft_error_messages(NEWLINE_ERROR), FAIL);
			else if (token->next->type != WORD)
				return (ft_error_messages(token->next->type), FAIL);
			new_infile = ft_create_new_infile(token->next->value, token->type);
			if (new_infile == NULL)
				return (FAIL);
			ft_add_infile(&new_cmd->infile_list, new_infile);
			token->attributed = true;
			token->next->attributed = true;
			token = token->next->next;
		}
		else
			token = token->next;
	}
	return (SUCCESS);
}

static int	parse_outfiles(t_cmd *new_cmd, t_token *token)
{
	t_outfile	*new_outfile;

	new_outfile = NULL;
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == RIGHT_TRUNC || token->type == APPEND)
		{
			if (token->next == NULL)
				return (ft_error_messages(NEWLINE_ERROR), FAIL);
			else if (token->next->type != WORD)
				return (ft_error_messages(token->next->type), FAIL);
			new_outfile = ft_create_new_outfile(token->next->value, token->type);
			if (new_outfile == NULL)
				return (FAIL);
			ft_add_outfile(&new_cmd->outfile_list, new_outfile);
			token->attributed = true;
			token->next->attributed = true;
			token = token->next->next;
		}
		else
			token = token->next;
	}
	return (SUCCESS);
}

static int	parse_commands(t_cmd *new_cmd, t_token *token)
{
	t_arg	*new_arg;

	new_arg = NULL;
	while (token != NULL && token->type != PIPE)
	{
		if (token->attributed == false)
		{
			new_arg = create_new_arg(token->value);
			if (!new_arg)
			{
				printf("FAIIIIL\n");
				return (FAIL);
			}
			add_new_arg(&new_cmd->arg_list, new_arg);
		}
		token = token->next;
	}
	return (SUCCESS);
}

t_cmd	*ft_create_cmd(t_token *cur_token)
{
	t_cmd	*new_cmd;

	if (cur_token == NULL)
		return (NULL);
	new_cmd = ft_create_new_cmd();
	if (!new_cmd)
		return (NULL);
	if (parse_infiles(new_cmd, cur_token) == FAIL)
		return (NULL);
	if (parse_outfiles(new_cmd, cur_token) == FAIL)
		return (NULL);
	if (parse_commands(new_cmd, cur_token) == FAIL)
		return (NULL);
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
			if (cur_token == NULL)
				return (cmd_list);
		}
		cur_token = cur_token->next;
	}
	return (cmd_list);
}
