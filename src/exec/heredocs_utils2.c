/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/02 09:56:22 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 12:09:41 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_get_file_name(int i)
{
	char	*file_num;
	char	*file_name;
	char	*tmp;

	file_name = NULL;
	file_num = NULL;
	file_num = ft_itoa(i);
	file_name = ft_strjoin(".tmp_hd", file_num);
	if (!file_name)
		return (NULL);
	if (access(file_name, F_OK) == 0)
	{
		free(file_name);
		tmp = ft_strjoin(file_num, "_");
		if (!tmp)
			return (free(file_num), NULL);
		file_name = ft_strjoin(".tmp_hd", tmp);
		if (!file_name)
			return (free(tmp), free(file_num), NULL);
		free(tmp);
	}
	if (file_num)
		free(file_num);
	return (file_name);
}

char	**ft_create_hd_filenames(int hdnum)
{
	char	**hd_files;
	int		i;

	hd_files = malloc(sizeof(char *) * (hdnum + 1));
	if (!hd_files)
		return (NULL);
	i = 0;
	while (i < hdnum)
	{
		hd_files[i] = ft_get_file_name(i);
		i++;
	}
	hd_files[i] = NULL;
	return (hd_files);
}
