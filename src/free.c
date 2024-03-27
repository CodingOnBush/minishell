/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:18:48 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/27 13:03:22 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_free_tokens(t_token **token_list)
{
	t_token	*cur_token;
	t_token	*next;

	if (*token_list == NULL)
		return ;
	cur_token = *token_list;
	while (cur_token != NULL)
	{
		next = cur_token->next;
		free(cur_token->str);
		free(cur_token);
		cur_token = next;
	}
}

void	ft_free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i] != NULL)
	{
		free(path[i]);
		i++;
	}
	free(path);
}

void	ft_free_arg_list(t_arg **arg_list)
{
	t_arg	*cur_arg;
	t_arg	*next;

	if (*arg_list == NULL)
		return ;
	cur_arg = *arg_list;
	while (cur_arg != NULL)
	{
		next = cur_arg->next;
		free(cur_arg->value);
		free(cur_arg);
		cur_arg = next;
	}
}

void	ft_free_infile_list(t_infile **infile_list)
{
	t_infile	*cur_infile;
	t_infile	*next;

	if (*infile_list == NULL)
		return ;
	cur_infile = *infile_list;
	while (cur_infile != NULL)
	{
		next = cur_infile->next;
		free(cur_infile->filename);
		free(cur_infile->delimiter);
		free(cur_infile);
		cur_infile = next;
	}
}

void	ft_free_outfile_list(t_outfile **outfile_list)
{
	t_outfile	*cur_outfile;
	t_outfile	*next;

	if (*outfile_list == NULL)
		return ;
	cur_outfile = *outfile_list;
	while (cur_outfile != NULL)
	{
		next = cur_outfile->next;
		free(cur_outfile->filename);
		free(cur_outfile);
		cur_outfile = next;
	}
}

void	ft_free_cmds(t_cmd **cmd_list)
{
	t_cmd	*cur_cmd;
	t_cmd	*next;

	if (*cmd_list == NULL)
		return ;
	cur_cmd = *cmd_list;
	while (cur_cmd != NULL)
	{
		next = cur_cmd->next;
		
		ft_free_tokens(&cur_cmd->token_list);
		ft_free_arg_list(&cur_cmd->arg_list);
		ft_free_infile_list(&cur_cmd->infile_list);
		ft_free_outfile_list(&cur_cmd->outfile_list);
		free(cur_cmd);
		cur_cmd = next;
	}
}
