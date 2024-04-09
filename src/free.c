/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/13 15:18:48 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/07 15:38:29 by momrane          ###   ########.fr       */
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
		if (cur_token->str)
			free(cur_token->str);
		free(cur_token);
		cur_token = next;
	}
	*token_list = NULL;
}

void	ft_free_arg_list(t_arg **arg_list)
{
	t_arg	*cur;
	t_arg	*next;

	cur = *arg_list;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur->value);
		free(cur);
		cur = next;
	}
	*arg_list = NULL;
}

void	ft_free_infiles(t_infile **infile_list)
{
	t_infile	*cur;
	t_infile	*next;

	cur = *infile_list;
	if (!cur)
		return ;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur->filename);
		free(cur->delimiter);
		free(cur);
		cur = next;
	}
	*infile_list = NULL;
}

void	ft_free_outfiles(t_outfile **outfile_list)
{
	t_outfile	*cur;
	t_outfile	*next;

	if (!outfile_list && !*outfile_list)
		return ;
	cur = *outfile_list;
	if (!cur)
		return ;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur->filename);
		free(cur);
		cur = next;
	}
	*outfile_list = NULL;
}

void	ft_free_args(char ***args)
{
	char	**tmp;
	int		i;

	i = 0;
	tmp = *args;
	while (tmp[i] != NULL)
		free(tmp[i++]);
	free(tmp);
	*args = NULL;
}

void	ft_free_cmd(t_cmd *cmd)
{
	if (cmd != NULL)
	{
		ft_print_cmd_list(cmd);
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

void	ft_free_path(char **path)
{
	int	i;

	i = 0;
	if (!path || !*path)
		return ;
	while (path[i] != NULL)
	{
		free(path[i]);
		i++;
	}
	free(path);
}

void	ft_free_infile_list(t_infile **infile_list)
{
	t_infile	*cur;
	t_infile	*next;

	cur = *infile_list;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur->filename);
		free(cur->delimiter);
		free(cur);
		cur = next;
	}
	*infile_list = NULL;
}

void	ft_free_outfile_list(t_outfile **outfile_list)
{
	t_outfile	*cur;
	t_outfile	*next;

	cur = *outfile_list;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur->filename);
		free(cur);
		cur = next;
	}
	*outfile_list = NULL;
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

void	ft_free_lexing_and_parsing(t_data *data)
{
	if (data->token_list != NULL)
		ft_free_tokens(&data->token_list);
	if (data->cmd_list != NULL)
		ft_free_cmd_list(&data->cmd_list);
}

void	unlink_and_free(t_data *data)
{
	int	i;

	i = 0;
	if (!data || !data->hd_files)
		return ;
	while (i < data->hdnum && data->hd_files[i] != NULL)
	{
		if (unlink(data->hd_files[i]) == -1)
			perror("perror unlink");
		if (data->hd_files[i])
		{
			free(data->hd_files[i]);
			data->hd_files[i] = NULL;
		}
		i++;
	}
	if (data->hd_files)
	{
		free(data->hd_files);
		data->hd_files = NULL;
	}
	if (data->fd_hd)
	{
		free(data->fd_hd);
		data->fd_hd = NULL;
	}
}

void	ft_free_exec(t_data *data)
{
	int	i;

	i = 0;
	if (data->ids)
	{
		free(data->ids);
		data->ids = NULL;
	}
	if (data->pipe_ends)
	{
		while (i < data->cmd_nb - 1)
		{
			if (data->pipe_ends[i])
				free(data->pipe_ends[i]);
			i++;
		}
		free(data->pipe_ends);
		data->pipe_ends = NULL;
	}
}

void	ft_free_pipe_ends(t_data *data)
{
	int	i;

	i = 0;
	if (data->pipe_ends)
	{
		ft_close_pipes(data);
		while (i < data->cmd_nb - 1)
		{
			if (data->pipe_ends[i])
				free(data->pipe_ends[i]);
			i++;
		}
		free(data->pipe_ends);
		data->pipe_ends = NULL;
	}
}

void	ft_free_all(t_data *data)
{
	if (data)
	{
		unlink_and_free(data);
		ft_free_lexing_and_parsing(data);
		ft_free_exec(data);
		if (data->path_list)
			ft_free_path(data->path_list);
		if (data->line)
			free(data->line);
		if (data->pipe_ends)
			ft_free_pipe_ends(data);
		if (data->env_list)
			ft_free_env_list(&data->env_list);
		free(data);
	}
}

void	ft_free_hd_files(t_data *data)
{
	int	i;

	i = 0;
	if (data->hd_files != NULL)
	{
		while (i < data->hdnum)
		{
			if (data->hd_files[i])
				free(data->hd_files[i]);
			i++;
		}
		free(data->hd_files);
		data->hd_files = NULL;
	}
}

void	ft_reset_data(t_data *data)
{
	if (data != NULL)
	{
		if (data->line != NULL)
		{
			free(data->line);
			data->line = NULL;
		}
		ft_free_cmd_list(&data->cmd_list);
		ft_free_tokens(&data->token_list);
		data->cmd_nb = 0;
		data->hdnum = 0;
		if (data->fd_hd != NULL)
		{
			free(data->fd_hd);
			data->fd_hd = NULL;
		}
		ft_free_hd_files(data);
		if (data->ids != NULL)
		{
			free(data->ids);
			data->ids = NULL;
		}
		ft_free_pipe_ends(data);
		// maybe free path_list and/or join_path
		data->step = 0;
	}
}

void	ft_free_env_list(t_env **env_list)
{
	t_env	*cur;
	t_env	*next;

	cur = *env_list;
	while (cur != NULL)
	{
		next = cur->next;
		free(cur->key);
		free(cur->value);
		free(cur);
		cur = next;
	}
	*env_list = NULL;
}
