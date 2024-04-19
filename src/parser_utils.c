/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:39:05 by allblue           #+#    #+#             */
/*   Updated: 2024/04/19 16:51:57 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_arg	*ft_create_arg_list(t_token *token)
{
	t_arg	*new;
	t_arg	*res;
	char	*str;

	res = NULL;
	while (token != NULL && token->type != PIPE)
	{
		if (token->attributed == false && ft_isop(token->str) == NO)
		{
			str = ft_strdup(token->str);
			if (!str)
				return (ft_free_arg_list(&res), NULL);
			new = ft_new_arg(str, token->type);
			if (!new)
				return (ft_free_arg_list(&res), NULL);
			ft_add_new_arg(&res, new);
		}
		token = token->next;
	}
	return (res);
}

static int	ft_get_arg_nbr(t_arg *arg_list)
{
	int	count;

	count = 0;
	while (arg_list)
	{
		count++;
		arg_list = arg_list->next;
	}
	return (count);
}

static char	**ft_create_args_array(t_arg *arg_list)
{
	char	**array;
	int		len;
	int		i;

	if (!arg_list)
		return (NULL);
	len = ft_get_arg_nbr(arg_list);
	array = malloc((len + 1) * sizeof(char *));
	if (!array)
		return (NULL);
	i = 0;
	while (i < len)
	{
		array[i] = ft_strdup(arg_list->value);
		i++;
		arg_list = arg_list->next;
	}
	array[i] = NULL;
	return (array);
}

static int	ft_init_new_cmd(t_data *data, t_cmd *new_cmd, t_token *cur_token)
{
	new_cmd->token_list = ft_extract_token(cur_token);
	if (!new_cmd->token_list)
		return (FAIL);
	new_cmd->infile_list = ft_create_infile_list(data, new_cmd->token_list);
	new_cmd->outfile_list = ft_create_outfile_list(new_cmd->token_list);
	new_cmd->arg_list = ft_create_arg_list(new_cmd->token_list);
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
