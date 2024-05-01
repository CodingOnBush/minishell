/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:59:56 by vvaudain          #+#    #+#             */
/*   Updated: 2024/05/01 17:19:36 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_get_file_name(int i)
{
	char	*file_num;
	char	*file_name;
	char	*tmp;

	file_name = NULL;
	file_num = NULL;
	file_num = ft_itoa(i);
	file_name = ft_strjoin("tmp_hd", file_num);
	if (!file_name)
		return (NULL);
	if (access(file_name, F_OK) == 0)
	{
		free(file_name);
		tmp = ft_strjoin(file_num, "_");
		if (!tmp)
			return (free(file_num), NULL);
		file_name = ft_strjoin("tmp_hd", tmp);
		if (!file_name)
			return (free(tmp), free(file_num), NULL);
		free(tmp);
	}
	if (file_num)
		free(file_num);
	return (file_name);
}

char	**ft_create_hd_filenames(int hdnum)
{
	char	**hd_files;
	int		i;

	hd_files = malloc(sizeof(char *) * (hdnum + 1));
	if (!hd_files)
		return (NULL);
	i = 0;
	while (i < hdnum)
	{
		hd_files[i] = ft_get_file_name(i);
		i++;
	}
	hd_files[i] = NULL;
	return (hd_files);
}

int	ft_is_error_to_print(t_token *list)
{
	t_token	*cur_token;

	cur_token = list;
	while (cur_token != NULL)
	{
		if (cur_token->error == true)
		{
			ft_print_err(cur_token->err_type);
			return (YES);
		}
		cur_token = cur_token->next;
	}
	return (NO);
}

t_infile	*ft_get_next_infile(t_infile *infile, char *name)
{
	t_infile	*cur_inf;

	cur_inf = infile;
	while (cur_inf)
	{
		if (cur_inf->filename == NULL && ft_strcmp(cur_inf->delimiter,
				name) == 0)
			return (cur_inf);
		cur_inf = cur_inf->next;
	}
	return (NULL);
}

void	ft_set_heredoc_files(t_data *data)
{
	t_token *cur_token;
	t_cmd *cur_cmd;
	t_infile *infile;
	int count;

	count = 0;
	cur_cmd = data->cmd_list;
	if (!cur_cmd)
		return ;
	infile = cur_cmd->infile_list;
	while (cur_cmd != NULL && count < data->hdnum)
	{
		cur_token = cur_cmd->token_list;
		while (cur_token)
		{
			if (cur_token->type == HD)
			{
				if (cur_token->next && cur_token->next->type == LIM)
				{
					cur_token->next->heredoc_file = data->hd_files[count];
					infile = ft_get_next_infile(infile, cur_token->next->value);
					if (infile)
						infile->filename = data->hd_files[count];
					infile = infile->next;
					count++;
				}
			}
			cur_token = cur_token->next;
		}
		cur_cmd = cur_cmd->next;
	}
}