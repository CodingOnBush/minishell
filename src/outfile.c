/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:19:03 by momrane           #+#    #+#             */
/*   Updated: 2024/03/20 14:48:48 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_outfile	*ft_create_new_outfile(char *filename)
{
	t_outfile	*new_outfile;

	new_outfile = malloc(sizeof(t_outfile));
	if (!new_outfile)
		return (NULL);
	new_outfile->filename = filename;
	new_outfile->append = false;
	new_outfile->next = NULL;
	return (new_outfile);
}

void	ft_add_outfile(t_outfile **outfile_list, t_outfile *new_outfile)
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
