/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 15:38:00 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/03 15:07:14 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_token	*ft_extract_token(t_token *token_list)
{
	t_token	*new_token;
	t_token	*sub_list;
	char	*new_str;

	sub_list = NULL;
	while (token_list != NULL && token_list->type != PIPE)
	{
		new_str = ft_strdup(token_list->str);
		if (!new_str)
			return (ft_free_tokens(&sub_list), NULL);
		new_token = ft_create_new_token(new_str, token_list->type, token_list->pos, token_list->error);
		if (!new_token)
			return (free(new_str), ft_free_tokens(&sub_list), NULL);
		ft_addlast_token(&sub_list, new_token);
		token_list = token_list->next;
	}
	return (sub_list);
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

int	parse_infiles(t_cmd *new_cmd, t_token *token)
{
	t_infile	*new_infile;

	new_infile = NULL;
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == LEFT_TRUNC || token->type == HERE_DOC)
		{
			if (token->next == NULL)
				return (assign_error(token, NEWLINE_ERROR), FAIL);
			// else if (token->next->type == PIPE)
			// {
			// 	printf("je suis heredoc\n");
			// 	return (assign_error(token, PIPE), FAIL);
			// }
			// else if (ft_isop(token->next->str) == YES)
			// 	return (assign_error(token->next, token->next->type), FAIL);
			new_infile = ft_create_new_infile(token->next->str, token->type);
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

int	parse_outfiles(t_cmd *new_cmd, t_token *token)
{
	t_outfile	*new_outfile;

	new_outfile = NULL;
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == RIGHT_TRUNC || token->type == APPEND)
		{
			if (token->next == NULL)
				return (assign_error(token, NEWLINE_ERROR), FAIL);
			else if (token->next->type != WORD)
				return (assign_error(token->next, token->next->type), FAIL);
			new_outfile = ft_create_new_outfile(token->next->str, token->type);
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

int	parse_commands(t_cmd *new_cmd, t_token *token)
{
	t_arg	*new_arg;
	char	*new_str;

	new_arg = NULL;
	while (token != NULL && token->type != PIPE)
	{
		if (token->attributed == false)
		{
			new_str = ft_strdup(token->str);
			if (!new_str)
				return (ft_free_arg_list(&new_cmd->arg_list), FAIL);
			new_arg = create_new_arg(new_str);
			if (!new_arg)
				return (ft_free_arg_list(&new_cmd->arg_list), FAIL);
			add_new_arg(&new_cmd->arg_list, new_arg);
		}
		token = token->next;
	}
	return (SUCCESS);
}
