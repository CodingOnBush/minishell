/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 12:32:35 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 12:32:36 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static void	ft_free_args(char ***args)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = *args;
	if (tmp == NULL)
		return ;
	while (tmp[i] != NULL)
	{
		if (tmp[i])
			free(tmp[i]);
		i++;
	}
	if (tmp)
		free(tmp);
	*args = NULL;
}

static void	ft_free_cmd(t_cmd *cmd)
{
	if (cmd != NULL)
	{
		if (cmd->token_list != NULL)
			ft_free_tokens(&cmd->token_list);
		if (cmd->arg_list != NULL)
			ft_free_arg_list(&cmd->arg_list);
		if (cmd->infile_list != NULL)
			ft_free_infiles(&cmd->infile_list);
		if (cmd->outfile_list != NULL)
			ft_free_outfiles(&cmd->outfile_list);
		if (cmd->args != NULL)
			ft_free_args(&cmd->args);
		if (cmd->cmd_path != NULL)
			free(cmd->cmd_path);
		free(cmd);
	}
}

void	ft_free_cmd_list(t_cmd **cmd_list)
{
	t_cmd	*cur_cmd;
	t_cmd	*next;

	cur_cmd = *cmd_list;
	while (cur_cmd != NULL)
	{
		next = cur_cmd->next;
		ft_free_cmd(cur_cmd);
		cur_cmd = next;
	}
	*cmd_list = NULL;
}

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
		if (cur_token->value)
			free(cur_token->value);
		if (cur_token->heredoc_file)
			free(cur_token->heredoc_file);
		free(cur_token);
		cur_token = next;
	}
	*token_list = NULL;
}

void	ft_free_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i])
	{
		free(env[i]);
		i++;
	}
	if (env)
		free(env);
}
