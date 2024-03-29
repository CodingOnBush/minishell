/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 13:48:50 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/29 11:48:12 by vvaudain         ###   ########.fr       */
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

int	do_heredocs(t_data *data)
{
    t_cmd   *cur_cmd;
    t_token *cur_token;
	int	    *fd_hd;
    int     i;

	data->hdnum = get_hd_number(data->cmd_list);
    printf("hdnum = %d\n", data->hdnum);
    i = 0;
	fd_hd = malloc (sizeof(int) * data->hdnum);
	if (!fd_hd)
		return (FAIL);
    // cur_cmd = data->cmd_list;
	// while (cur_cmd != NULL)
    // {
    //     cur_token = cur_cmd->token_list;
    //     while (cur_token != NULL || cur_token->error == false)
    //         cur_token = cur_token->next;
    //     if (cur_token == NULL)
    //     {
    //         //on va executer les heredocs de la commande
    //     }
    //     else
    //         break;
    //     cur_cmd = cur_cmd->next;
    // }
    // /*si on arrive ici et que cur_cmd est NULL, on a fini de traiter 
    // les heredocs sinon c'est qu'il y a une erreur et donc qu'il 
    // faut regarder ou est cette erreur et de quel type elle est pour
    // voir si d'autres heredocs sont a executer*/
    return (SUCCESS);
}