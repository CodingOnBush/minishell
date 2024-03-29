/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:48:50 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/29 18:14:44 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char **create_hd_files(int hdnum)
{
    char    **hd_files;
    int     i;
    char    *file_num;

    hd_files = malloc(sizeof(char *) * hdnum);
    if (!hd_files)
        return (NULL);
    i = 0;
    while (i < hdnum)
    {
        file_num = ft_itoa(i);
        hd_files[i] = ft_strjoin("tmp_hd", file_num);
        free(file_num);
        if (!hd_files[i])
            return (NULL);
        i++;
    }
    return (hd_files);
}

static void remove_if_hd_exists(t_data *data, char *hd_file)
{
    if (access(hd_file, F_OK) == 0)
    {
        if (unlink(hd_file) == -1)
        {
            ft_putstr_fd("Error while removing hd file\n", 2);
            ft_free_tokens(&data->token_list);
            ft_free_cmds(&data->cmd_list);
        }
    }
}

void    writing_loop(t_data *data, int fd_hd, char *delimiter)
{
    char    *line;
    size_t  len;

    while (1)
    {
		line = readline("> ");
		if (!line)
		{
			ft_putstr_fd("warning: here-document delimited by end of file\n", 2);
			break ;
		}
		len = ft_strlen((const char *)line);
		if (ft_strncmp(line, delimiter, len) == 0)
			break ;
		else
		{
			write(fd_hd, line, len);
			free(line);
		}
	}
	free(line);
}

static int execute_hd(t_data *data, t_cmd *cmd, int *fd_hd, int i)
{
    t_infile    *cur_inf;

    cur_inf = cmd->infile_list;
    while (cur_inf != NULL && i < data->hdnum)
    {
        if (cur_inf->delimiter != NULL)
        {
            remove_if_hd_exists(data, data->hd_files[i]);
            fd_hd[i] = open(data->hd_files[i], O_WRONLY | O_CREAT, 0644);
            if (fd_hd[i] == -1)
                return(ft_error_messages(HDEXEC), ft_free_tokens(&data->token_list), ft_free_cmds(&data->cmd_list), FAIL);
            writing_loop(data, fd_hd[i], cur_inf->delimiter);
            close(fd_hd[i]);
            i++;
        }
        cur_inf = cur_inf->next;
    }
    return (i);
}

int	do_heredocs(t_data *data)
{
    t_cmd       *cur_cmd;
    int         i;

	data->hdnum = get_hd_number(data->cmd_list);
    i = 0;
	data->fd_hd = malloc (sizeof(int) * data->hdnum);
	if (!data->fd_hd)
		return (FAIL);
    data->hd_files = create_hd_files(data->hdnum);
    if (!data->hd_files)
        return (FAIL);
    cur_cmd = data->cmd_list;
	while (cur_cmd != NULL && i < data->hdnum)
    {
        i += execute_hd(data, cur_cmd, data->fd_hd, i);
        if (i == data->hdnum)
            return (SUCCESS);
        else
            cur_cmd = cur_cmd->next;
    }
    return (FAIL);
}
