/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:23:11 by momrane           #+#    #+#             */
/*   Updated: 2024/04/17 14:17:37 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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

// int	parse_infiles(t_data *data, t_cmd *new_cmd, t_token *token)
// {
// 	t_infile	*new_infile;

// 	new_infile = NULL;
// 	while (token != NULL && token->type != PIPE)
// 	{
// 		if (token->type == LEFT_TRUNC || token->type == HERE_DOC)
// 		{
// 			if (token->next == NULL)
// 				return (assign_error(token, NEWLINE_ERROR), FAIL);
// 			// else if (token->next->type == PIPE)
// 			// {
// 			// 	printf("je suis heredoc\n");
// 			// 	return (assign_error(token, PIPE), FAIL);
// 			// }
// 			// else if (ft_isop(token->next->str) == YES)
// 			// 	return (assign_error(token->next, token->next->type), FAIL);
// 			new_infile = ft_new_infile(token->next->str, token->type, data);
// 			if (new_infile == NULL)
// 				return (FAIL);
// 			ft_add_infile(&new_cmd->infile_list, new_infile);
// 			token->attributed = true;
// 			token->next->attributed = true;
// 			token = token->next->next;
// 		}
// 		else
// 			token = token->next;
// 	}
// 	return (SUCCESS);
// }

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
			new_outfile = ft_new_outfile(token->next->str, token->type);
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
			new_arg = ft_new_arg(new_str, token->type);
			if (!new_arg)
				return (ft_free_arg_list(&new_cmd->arg_list), FAIL);
			ft_add_new_arg(&new_cmd->arg_list, new_arg);
		}
		token = token->next;
	}
	return (SUCCESS);
}

char	*ft_type_to_str(int type)
{
	if (type == PIPE)
		return ("PIPE");
	if (type == PIPE_AT_END)
		return ("PIPE_AT_END");
	if (type == HERE_DOC)
		return ("HEREDOC");
	if (type == APPEND)
		return ("APPEND");
	if (type == LEFT_TRUNC)
		return ("LTRUNC");
	if (type == RIGHT_TRUNC)
		return ("RTRUNC");
	if (type == WORD)
		return ("WORD");
	if (type == NEWLINE_ERROR)
		return ("ERRNEWLINE");
	if (type == QUOTES_ERROR)
		return ("ERRQUOTE");
	if (type == SINGLE_QUOTE_ERROR)
		return ("SINGLE_QUOTE_ERROR");
	if (type == DOUBLE_QUOTE_ERROR)
		return ("DOUBLE_QUOTE_ERROR");
	if (type == QWORD)
		return ("QWORD");
	if (type == LIM)
		return ("LIM");
	return ("UNKNOWN");
}

void	ft_print_token_list(t_token *list)
{
	t_token	*tmp;

	tmp = list;
	printf("TOKEN LIST\n");
	if (!tmp)
		printf("nil");
	while (tmp)
	{
		printf("%s\t\t%s\t\t%d\t%d\t%d\t%s\n", tmp->str, ft_type_to_str(tmp->type), tmp->attributed, tmp->pos, tmp->error, ft_type_to_str(tmp->err_type));
		tmp = tmp->next;
	}
}

void	ft_print_arg_list(t_arg *list)
{
	t_arg	*tmp;

	tmp = list;
	printf("ARGLIST\t:");
	if (!tmp)
		printf("nil");
	while (tmp)
	{
		printf("[%s]", tmp->value);
		tmp = tmp->next;
	}
	printf("\n");
}

static void	ft_print_infile_list(t_infile *list)
{
	t_infile	*tmp;

	tmp = list;
	printf("INFILE\t:");
	if (!tmp)
		printf("nil");
	while (tmp)
	{
		printf("[name : %s | delim : %s]", tmp->filename, tmp->delimiter);
		tmp = tmp->next;
	}
	printf("\n");
}

static void	ft_print_outfile_list(t_outfile *list)
{
	t_outfile	*tmp;

	tmp = list;
	printf("OUTFILE\t:");
	if (!tmp)
		printf("nil");
	while (tmp != NULL)
	{
		if (tmp->filename)
			printf("[name : %s | is_append : %d]", tmp->filename, tmp->append);
		tmp = tmp->next;
	}
	printf("\n");
}

void	ft_print_cmd_list(t_cmd *list)
{
	t_cmd	*tmp;

	tmp = list;
	if (!tmp)
		printf("cmd list empty\n");
	while (tmp)
	{
		printf("=========== CMD (%d)==========\n", tmp->pos);
		printf("tmp->cmd_path : %s\n", tmp->cmd_path);
		ft_print_token_list(tmp->token_list);
		ft_print_arg_list(tmp->arg_list);
		ft_print_infile_list(tmp->infile_list);
		ft_print_outfile_list(tmp->outfile_list);
		printf("===========================\n");
		tmp = tmp->next;
	}
}
