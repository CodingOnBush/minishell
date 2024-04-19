/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:50:01 by momrane           #+#    #+#             */
/*   Updated: 2024/04/19 16:59:52 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*		ARGS		*/
t_arg		*ft_new_arg(char *value, int token_type);
void		ft_add_new_arg(t_arg **head, t_arg *new_arg);

/*		INFILE		*/
// t_infile	*ft_new_infile(char *str, int type, t_data *data);
// void		ft_set_hd_as_infiles(t_data *data);
// void		ft_add_infile(t_infile **infile_list, t_infile *new_infile);
t_infile	*ft_create_infile_list(t_data *data, t_token *cur_token);

/*		OUTFILE		*/
// t_outfile	*ft_new_outfile(char *filename, int type);
// void		ft_add_outfile(t_outfile **outfile_list, t_outfile *new_outfile);
t_outfile	*ft_create_outfile_list(t_token *cur_token);

/*	PARSER_UTILS	*/
t_cmd		*ft_new_cmd(t_data *data, t_token *cur_token, int pos);
void		ft_add_new_cmd(t_cmd **cmd_list, t_cmd *new_cmd);
// int			ft_get_cmd_nb(t_cmd *cmd_list);

/*		PARSER		*/
int			ft_parser(t_data *data);

#endif