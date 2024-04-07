/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:19:03 by momrane           #+#    #+#             */
/*   Updated: 2024/04/07 14:33:50 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_infile	*ft_new_infile(char *str, int type)
{
	t_infile	*new_infile;
	char		*new_str;

	new_infile = malloc(sizeof(t_infile));
	if (!new_infile)
		return (NULL);
	new_str = ft_strdup(str);
	if (!new_str)
		return (free(new_infile), NULL);
	if (type == LEFT_TRUNC)
	{
		new_infile->filename = new_str;
		new_infile->delimiter = NULL;
	}
	else if (type == HERE_DOC)
	{
		new_infile->filename = NULL;
		new_infile->delimiter = new_str;
	}
	new_infile->next = NULL;
	return (new_infile);
}

void	ft_add_infile(t_infile **infile_list, t_infile *new_infile)
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

t_infile	*ft_create_infile_list(t_token *cur_token)
{
	t_infile	*res;
	t_infile	*new;

	res = NULL;
	while (cur_token)
	{
		if (cur_token->type == LEFT_TRUNC || cur_token->type == HERE_DOC)
		{
			new = ft_new_infile(cur_token->str, cur_token->type);
			if (!new)
				return (ft_free_infiles(&res), NULL);
			ft_add_infile(&res, new);
		}
		cur_token = cur_token->next;
	}
	return (res);
}
