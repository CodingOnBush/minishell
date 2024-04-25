/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:31:42 by momrane           #+#    #+#             */
/*   Updated: 2024/04/25 14:40:54 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_exit_builtin(t_data *data)
{
	t_cmd	*cmd;

	if (!data || !data->cmd_list)
		return (NO);
	cmd = data->cmd_list;
	if (!cmd->args)
		return (NO);
	while (cmd)
	{
		if (ft_strncmp(cmd->args[0], "exit", ft_strlen("exit")) == 0)
			return (YES);
		cmd = cmd->next;
	}
	return (NO);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}

int	ft_get_env_list_size(t_env *env)
{
	int		i;
	t_env	*cur;

	i = 0;
	cur = env;
	while (cur)
	{
		i++;
		cur = cur->next;
	}
	return (i);
}

int	ft_get_arg_list_size(t_arg *arg_list)
{
	int	i;

	i = 0;
	while (arg_list != NULL)
	{
		i++;
		arg_list = arg_list->next;
	}
	return (i);
}

int	ft_file_is_append(t_cmd *cmd, char *filename)
{
	t_outfile	*cur_outf;

	cur_outf = cmd->outfile_list;
	while (cur_outf != NULL)
	{
		if (ft_strcmp(cur_outf->filename, filename) == 0)
		{
			if (cur_outf->append == true)
				return (YES);
			else
				return (NO);
		}
		cur_outf = cur_outf->next;
	}
	return (FAIL);
}
