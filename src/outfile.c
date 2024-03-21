/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 14:19:03 by momrane           #+#    #+#             */
/*   Updated: 2024/03/21 10:58:57 by vvaudain         ###   ########.fr       */
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

int	set_outfile_list(t_cmd *cmd, t_token *token)
{
	t_outfile	*new_outfile;

	new_outfile = NULL;
	while (token != NULL && token->type != PIPE)
	{
		if (token->type == RIGHT_TRUNC)
		{
			if (token->next != NULL && token->next->type == WORD)
			{
				new_outfile = ft_create_new_outfile(token->next->value);
				if (new_outfile == NULL)
					return (FAIL);
				ft_add_outfile(&cmd->outfile_list, new_outfile);
			}
			else if (token->next != NULL && ft_isoperator(token->next->value) != 0)
				return (ft_error_messages(token->next->type), FAIL);
			else if (token->next == NULL)
				return (ft_error_messages(NEWLINE_ERROR), FAIL);
		}
		token = token->next;
	}
	return (SUCCESS);
}