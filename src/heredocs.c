/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:48:50 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/29 14:33:43 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int  get_err_pos(t_cmd *cmd)
{
   t_token *cur_token;
   int     err_pos;


   err_pos = -1;
   cur_token = cmd->token_list;
   while(cur_token != NULL)
   {
       if (cur_token->error == true)
       {
           err_pos = cur_token->pos;
           return (err_pos);
       }
       cur_token = cur_token->next;
   }
   return (err_pos);
}


static int  count_hd_pre_error(t_cmd *cmd)
{
   t_token *cur;
   int     err_pos;
   int     hd_count;
   int     i;


   if (cmd == NULL)
       return (0);
   err_pos = 0;
   hd_count = 0;
   i = 0;
   err_pos = get_err_pos(cmd);
   printf("err_pos = %d\n", err_pos);
   cur = cmd->token_list;
   while (cur != NULL && cur->pos < err_pos)
   {
       if (cur->type == HERE_DOC && cur->next != NULL && cur->next->type == WORD
           && cur->error == false && cur->next->error == false)
           hd_count++;
       cur = cur->next;
   }
   return (hd_count);
}


static int  count_heredocs(t_infile *inf_list)
{
   t_infile    *cur_inf;
   int         hd_count;


   if (inf_list == NULL)
       return (0);
   cur_inf = inf_list;
   hd_count = 0;
   while (cur_inf != NULL)
   {
       if (cur_inf->delimiter != NULL)
           hd_count++;
       cur_inf = cur_inf->next;
   }
   return (hd_count);
}

static int  get_hd_number(t_cmd *list)
{
   int     hdnum;
   t_cmd   *cur_cmd;
   t_token *cur_token;


   hdnum = 0;
   cur_cmd = list;
   while (cur_cmd != NULL)
   {
       cur_token = cur_cmd->token_list;
       while(cur_token != NULL)
       {
           if (cur_token->error == true)
               break ;
           cur_token = cur_token->next;
       }
       if (cur_token != NULL && cur_token->error == true)
            break ;
       hdnum += count_heredocs(cur_cmd->infile_list);
       cur_cmd = cur_cmd->next;
   }
   if (cur_cmd != NULL && cur_token->error == true)
       hdnum += count_hd_pre_error(cur_cmd);
   return (hdnum);
}

static char **create_hd_files(int hdnum)
{
    char    **hd_files;
    int     i;

    hd_files = malloc(sizeof(char *) * hdnum);
    if (!hd_files)
        return (NULL);
    i = 0;
    while (i < hdnum)
    {
        hd_files[i] = ft_strjoin("tmp_hd", ft_itoa(i));
        printf("hd_files[%d] = %s\n", i, hd_files[i]);
        if (!hd_files[i])
            return (NULL);
        i++;
    }
    return (hd_files);
}

// static void remove_if_hd_exists(char *hd_file)
// {
//     if (access(hd_file, F_OK) == 0)
//     {
//         if (unlink(hd_file) == -1)
//         {
//             printf("Error while removing hd file\n");
//             ft_free
//         }
//     }
// }

int	do_heredocs(t_data *data)
{
    t_cmd       *cur_cmd;
    t_infile    *cur_infile;
	int	        *fd_hd;
    int         i;

	data->hdnum = get_hd_number(data->cmd_list);
    printf("hdnum = %d\n", data->hdnum);
    i = 0;
	fd_hd = malloc (sizeof(int) * data->hdnum);
	if (!fd_hd)
		return (FAIL);
    cur_cmd = data->cmd_list;
    data->hd_files = create_hd_files(data->hdnum);
	// while (cur_cmd != NULL && i < data->hdnum)
    // {
    //     cur_infile = cur_cmd->infile_list;
    //     while (cur_infile != NULL && i < data->hdnum)
    //     {
    //         if (cur_infile->delimiter != NULL)
    //         {
    //             remove_if_hd_exists(data->hd_files[i]);
    //             fd_hd[i] = open(data->hd_files[i], O_WRONLY | O_CREAT, 0644);
    //             i++;
    //         }
    //         cur_infile = cur_infile->next;
    //     }
    //     cur_cmd = cur_cmd->next;
    // }
    return (SUCCESS);
}