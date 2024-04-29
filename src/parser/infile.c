/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:19:03 by momrane           #+#    #+#             */
/*   Updated: 2024/04/29 13:57:33 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_infile	*ft_new_infile(char *str, int type, t_data *data, bool to_exp)
{
	t_infile	*new_infile;
	char		*new;

	new_infile = malloc(sizeof(t_infile));
	if (!new_infile)
		return (NULL);
	new = ft_strdup(str);
	if (!new)
		return (free(new_infile), NULL);
	new_infile->to_expand = true;
	new_infile->filename = NULL;
	if (type == LEFT_TRUNC)
	{
		new_infile->filename = new;
		new_infile->delimiter = NULL;
	}
	else if (type == HERE_DOC)
	{
		new_infile->hd_num = data->hd_pos;
		data->hd_pos++;
		new_infile->delimiter = new;
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

t_infile	*ft_create_infile_list(t_data *data, t_token *cur)
{
	t_infile	*res;
	t_infile	*new;
	t_token		*nxt;

	res = NULL;
	new = NULL;
	while (cur)
	{
		nxt = cur->next;
		if ((cur->type == LEFT_TRUNC || cur->type == HERE_DOC) && cur->error == false)
		{
			if (nxt && (nxt->type == WORD || nxt->type == LIM) && nxt->error == false)
			{
				new = ft_new_infile(nxt->value, cur->type, data, nxt->to_expand);
				if (!new)
					return (ft_free_infiles(&res), NULL);
				nxt->attributed = true;
				if (nxt->type == LIM && nxt->to_expand == false)
					new->to_expand = false;
				if (nxt->type == WORD)
					nxt->is_inf = true;
			}
			cur->attributed = true;
			ft_add_infile(&res, new);
		}
		if (cur->error == true)
			break;
		cur = nxt;
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
		if (cur->filename && cur->delimiter)
			free(cur->delimiter);
		if (cur->delimiter == NULL && cur->filename)
			free(cur->filename);
		free(cur);
		cur = next;
	}
	*infile_list = NULL;
}
