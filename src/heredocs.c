/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:48:50 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/26 14:53:57 by vvaudain         ###   ########.fr       */
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
       hdnum += count_heredocs(cur_cmd->infile_list);
       cur_cmd = cur_cmd->next;
   }
   if (cur_cmd != NULL)
       hdnum += count_hd_pre_error(cur_cmd);
   return (hdnum);
}

int	do_heredocs(t_data *data)
{
	int	*fd_hd;

	data->hdnum = get_hd_number();
	fd_hd = malloc (sizeof(int) * data->hdnum);
	if (!fd_hd)
		return (FAIL);
	
	
}