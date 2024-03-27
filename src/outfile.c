/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:19:03 by momrane           #+#    #+#             */
/*   Updated: 2024/03/27 15:18:51 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

t_outfile	*ft_create_new_outfile(char *filename, int type)
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
