/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:23:11 by momrane           #+#    #+#             */
/*   Updated: 2024/04/20 00:52:03 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_type_to_str(int type)
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

void	ft_print_env_list(t_env *env_list)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		printf("key : %s | ", tmp->key);
		printf("value : %s\n", tmp->value);
		tmp = tmp->next;
	}
}
