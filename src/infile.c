/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:19:03 by momrane           #+#    #+#             */
/*   Updated: 2024/03/21 17:15:56 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_infile	*ft_create_new_infile(char *str, int type)
{
	t_infile	*new_infile;

	new_infile = malloc(sizeof(t_infile));
	if (!new_infile)
		return (NULL);
	if (type == LTRUNC)
	{
		new_infile->filename = str;
		new_infile->delimiter = NULL;
	}
	else if (type == HEREDOC)
	{
		new_infile->filename = NULL;
		new_infile->delimiter = str;
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
