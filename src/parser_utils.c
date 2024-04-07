/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/07 00:39:05 by allblue           #+#    #+#             */
/*   Updated: 2024/04/07 15:22:29 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_create_cmd_path(char *path, char *cmd_name)
{
	char	*cmd_path;
	char	*tmp;

	tmp = ft_strjoin(path, "/");
	if (!tmp)
		return (NULL);
	cmd_path = ft_strjoin(tmp, cmd_name);
	if (!cmd_path)
		return (NULL);
	free(tmp);
	return (cmd_path);
}

static char	*ft_get_cmd_path(char *cmd_name)
{
	char	**path_list;
	char	*cmd_path;
	int		i;

	path_list = ft_split(getenv("PATH"), ':');
	if (!path_list)
		return (NULL);
	i = 0;
	while (path_list[i])
	{
		cmd_path = ft_create_cmd_path(path_list[i], cmd_name);
		if (!cmd_path)
			return (ft_free_path(path_list), NULL);
		if (access(cmd_path, F_OK) == 0)
			return (ft_free_path(path_list), cmd_path);
		free(cmd_path);
		i++;
	}
	return (ft_free_path(path_list), NULL);
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
	new_cmd->outfile_list = ft_create_outfile_list(cur_token);
	new_cmd->args = ft_create_args_array(new_cmd->arg_list);
	new_cmd->cmd_path = ft_get_cmd_path(new_cmd->args[0]);
	new_cmd->next = NULL;
	return (SUCCESS);
}

t_cmd	*ft_new_cmd(t_token *cur_token, int pos)
{
	t_cmd	*new_cmd;

	if (!cur_token)
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
