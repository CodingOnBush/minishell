/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:19:03 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 12:43:36 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_infile	*ft_new_infile(char *str, int type, t_data *data)
{
	t_infile	*new_infile;

	new_infile = malloc(sizeof(t_infile));
	if (!new_infile)
		return (NULL);
	new_infile->to_expand = true;
	new_infile->hd_num = 0;
	if (type == LT)
	{
		new_infile->filename = ft_strdup(str);
		if (!new_infile->filename)
			new_infile->filename = NULL;
		new_infile->delimiter = NULL;
	}
	else if (type == HD)
	{
		new_infile->filename = NULL;
		new_infile->hd_num = data->hd_pos;
		data->hd_pos++;
		new_infile->delimiter = ft_strdup(str);
		if (!new_infile->delimiter)
			new_infile->delimiter = NULL;
	}
	new_infile->next = NULL;
	return (new_infile);
}

static void	ft_add_infile(t_infile **infile_list, t_infile *new_infile)
{
	t_infile	*lst;

	if (*infile_list == NULL)
		*infile_list = new_infile;
	else
	{
		lst = *infile_list;
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = new_infile;
	}
}

static t_infile	*ft_create_this_infile(t_token *nxt, t_token *cur, t_data *data)
{
	t_infile	*res;

	res = ft_new_infile(nxt->value, cur->type, data);
	if (!res)
		return (NULL);
	nxt->attributed = true;
	if (nxt->type == LIM && nxt->to_expand == false)
		res->to_expand = false;
	if (nxt->type == WORD)
		nxt->is_inf = true;
	return (res);
}

t_infile	*ft_create_infile_list(t_data *data, t_token *cur)
{
	t_infile	*res;
	t_infile	*new;

	res = NULL;
	new = NULL;
	while (cur)
	{
		if ((cur->type == LT || cur->type == HD) && cur->error == false)
		{
			if (cur->next && (cur->next->type == WORD || cur->next->type == LIM)
				&& cur->next->error == false)
			{
				new = ft_create_this_infile(cur->next, cur, data);
				if (!new)
					return (ft_free_infiles(&res), NULL);
			}
			cur->attributed = true;
			ft_add_infile(&res, new);
		}
		if (cur->error == true)
			break ;
		cur = cur->next;
	}
	return (res);
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
		if (cur->filename)
			free(cur->filename);
		if (cur->delimiter)
			free(cur->delimiter);
		free(cur);
		cur = next;
	}
	*infile_list = NULL;
}
