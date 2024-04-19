/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:19:03 by momrane           #+#    #+#             */
/*   Updated: 2024/04/19 16:53:01 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static t_infile	*ft_new_infile(char *str, int type, t_data *data)
{
	t_infile	*new_infile;
	char		*new_str;

	new_infile = malloc(sizeof(t_infile));
	if (!new_infile)
		return (NULL);
	new_str = ft_strdup(str);
	if (!new_str)
		return (free(new_infile), NULL);
	new_infile->to_expand = true;
	if (type == LEFT_TRUNC)
	{
		new_infile->filename = new_str;
		new_infile->delimiter = NULL;
	}
	else if (type == HERE_DOC)
	{
		new_infile->hd_num = data->hd_pos;
		data->hd_pos++;
		new_infile->delimiter = new_str;
		// new_infile->to_expand = true;
		if (ft_strchr(new_str, '\'') != NULL || ft_strchr(new_str, '\"') != NULL)
			new_infile->to_expand = false;
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

	res = NULL;
	new = NULL;
	while (cur)
	{
		if ((cur->type == LEFT_TRUNC || cur->type == HERE_DOC) && cur->error == false)
		{
			if (cur->next && (cur->next->type == WORD || cur->next->type == LIM) && cur->next->error == false)
			{
				new = ft_new_infile(cur->next->str, cur->type, data);
				if (!new)
					return (ft_free_infiles(&res), NULL);
				cur->attributed = true;
				cur->next->attributed = true;
				ft_add_infile(&res, new);
			}
			cur = cur->next;
		}
		else
			cur = cur->next;
	}
	return (res);
}
