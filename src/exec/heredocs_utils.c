/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:59:56 by vvaudain          #+#    #+#             */
/*   Updated: 2024/05/02 12:22:17 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
	if (cur_inf == NULL)
		return (NULL);
	while (cur_inf)
	{
		if (cur_inf->filename == NULL && ft_strcmp(cur_inf->delimiter,
				name) == 0)
			return (cur_inf);
		cur_inf = cur_inf->next;
	}
	return (NULL);
}

static int	ft_inside(t_token *cur_token, t_infile *given_infile, t_data *data,
		int count)
{
	t_infile	*infile;
	int			i;

	infile = given_infile;
	i = 0;
	while (cur_token)
	{
		if (cur_token->type == HD)
		{
			if (cur_token->next && cur_token->next->type == LIM)
			{
				cur_token->next->heredoc_file = ft_strdup(data->hd_files[count
						+ i]);
				infile = ft_get_next_infile(infile, cur_token->next->value);
				if (!infile)
					return (i);
				if (infile)
					infile->filename = ft_strdup(data->hd_files[count + i]);
				infile = infile->next;
				i++;
			}
		}
		cur_token = cur_token->next;
	}
	return (i);
}

void	ft_set_heredoc_files(t_data *data)
{
	t_token		*cur_token;
	t_cmd		*cur_cmd;
	t_infile	*infile;
	int			count;

	count = 0;
	cur_cmd = data->cmd_list;
	if (!cur_cmd)
		return ;
	infile = cur_cmd->infile_list;
	while (cur_cmd != NULL && count < data->hdnum)
	{
		cur_token = cur_cmd->token_list;
		count += ft_inside(cur_token, infile, data, count);
		cur_cmd = cur_cmd->next;
	}
}
