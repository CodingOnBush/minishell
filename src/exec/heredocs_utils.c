/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:59:56 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/26 10:31:53 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	**create_hd_files(int hdnum)
{
	char	**hd_files;
	int		i;

	hd_files = malloc(sizeof(char *) * (hdnum + 1));
	if (!hd_files)
		return (NULL);
	i = 0;
	while (i < hdnum)
	{
		hd_files[i] = get_file_name(i);
		i++;
	}
	hd_files[i] = NULL;
	return (hd_files);
}

char	*get_file_name(int i)
{
	char	*file_num;
	char	*file_name;
	char	*tmp;

	file_name = NULL;
	file_num = NULL;
	file_num = ft_itoa(i);
	file_name = ft_strjoin("tmp_hd", file_num);
	if (!file_name)
		return (NULL);
	if (access(file_name, F_OK) == 0)
	{
		free(file_name);
		tmp = ft_strjoin(file_num, "_");
		if (!tmp)
			return (free(file_num), NULL);
		file_name = ft_strjoin("tmp_hd", tmp);
		if (!file_name)
			return (free(tmp), free(file_num), NULL);
		free(tmp);
	}
	if (file_num)
		free(file_num);
	return (file_name);
}

int	is_error_to_print(t_token *list)
{
	t_token	*cur_token;

	cur_token = list;
	while (cur_token != NULL)
	{
		if (cur_token->error == true)
		{
			ft_print_error(cur_token->err_type);
			return (YES);
		}
		cur_token = cur_token->next;
	}
	return (NO);
}
