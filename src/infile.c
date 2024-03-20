/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:19:03 by momrane           #+#    #+#             */
/*   Updated: 2024/03/20 14:45:07 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_infile	*ft_create_new_infile(char *filename)
{
	t_infile	*new_infile;

	new_infile = malloc(sizeof(t_infile));
	if (!new_infile)
		return (NULL);
	new_infile->filename = filename;
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
