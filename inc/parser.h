/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:50:01 by momrane           #+#    #+#             */
/*   Updated: 2024/04/10 16:53:50 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*		ARGS		*/
t_arg		*ft_new_arg(char *value);
void		ft_add_new_arg(t_arg **head, t_arg *new_arg);
t_arg		*ft_create_arg_list(t_token *token);
char		**ft_create_args_array(t_arg *arg_list);

/*		INFILE		*/
t_infile	*ft_new_infile(char *str, int type);
void		ft_add_infile(t_infile **infile_list, t_infile *new_infile);
t_infile	*ft_create_infile_list(t_token *cur_token);

/*		OUTFILE		*/
t_outfile	*ft_new_outfile(char *filename, int type);
void		ft_add_outfile(t_outfile **outfile_list, t_outfile *new_outfile);
t_outfile	*ft_create_outfile_list(t_token *cur_token);

/*	PARSER_UTILS	*/
t_cmd		*ft_new_cmd(t_token *cur_token, int pos);
void		ft_add_new_cmd(t_cmd **cmd_list, t_cmd *new_cmd);
int			ft_get_cmd_nb(t_cmd *cmd_list);

/*		PARSER		*/
int			ft_parser(t_data *data);

#endif