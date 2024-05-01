/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:19:03 by momrane           #+#    #+#             */
/*   Updated: 2024/05/01 17:03:10 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static t_outfile	*ft_new_outfile(char *filename, int type)
{
	t_outfile	*new_outfile;
	char		*new_str;

	new_outfile = malloc(sizeof(t_outfile));
	if (!new_outfile)
		return (NULL);
	new_str = ft_strdup(filename);
	if (!new_str)
		return (free(new_outfile), NULL);
	new_outfile->filename = new_str;
	new_outfile->append = false;
	if (type == APPEND)
		new_outfile->append = true;
	new_outfile->next = NULL;
	return (new_outfile);
}

static void	ft_add_outfile(t_outfile **outfile_list, t_outfile *new_outfile)
{
	t_outfile	*lst;

	if (*outfile_list == NULL)
		*outfile_list = new_outfile;
	else
	{
		lst = *outfile_list;
		while (lst->next != NULL)
			lst = lst->next;
		lst->next = new_outfile;
	}
}

t_outfile	*ft_create_outfile_list(t_token *cur)
{
	t_outfile	*outfile_list;
	t_outfile	*new_outfile;

	outfile_list = NULL;
	new_outfile = NULL;
	while (cur)
	{
		if ((cur->type == RIGHT_TRUNC || cur->type == APPEND)
			&& cur->error == false)
		{
			if (cur->next && cur->next->value
				&& ft_isop(cur->next->value) == NO)
				new_outfile = ft_new_outfile(cur->next->value, cur->type);
			if (!new_outfile)
				return (ft_free_outfiles(&outfile_list), NULL);
			cur->attributed = true;
			cur->next->attributed = true;
			cur->next->is_outf = true;
			ft_add_outfile(&outfile_list, new_outfile);
			cur = cur->next;
		}
		else
			cur = cur->next;
	}
	return (outfile_list);
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
		if (cur->filename)
			free(cur->filename);
		free(cur);
		cur = next;
	}
	*outfile_list = NULL;
}
