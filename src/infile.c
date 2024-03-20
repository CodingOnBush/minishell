/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:19:03 by momrane           #+#    #+#             */
/*   Updated: 2024/03/20 17:18:31 by vvaudain         ###   ########.fr       */
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

void	set_infile_list(t_cmd *cmd, t_token *token)
{
	t_infile	*new_infile;
	
	new_infile = NULL;
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == LEFT_TRUNC)
		{
			if (token->next != NULL && token->next->type == WORD)
			{
				new_infile = ft_create_new_infile(token->next->value);
				if (new_infile == NULL)
					return ;
				ft_add_infile(&cmd->infile_list, new_infile);
			}
			else if (token->next != NULL && ft_isoperator(token->next->value) != 0)
				return (ft_error_messages(token->next->value));
			else if (token->next == NULL)
				return (ft_error_messages("`newline'"));
		}
		token = token->next;
	}
	return ;
}