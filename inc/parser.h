/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:50:01 by momrane           #+#    #+#             */
/*   Updated: 2024/04/21 12:37:59 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/*		ARGS		*/
t_arg		*ft_create_arg_list(t_token *token);
void		ft_free_arg_list(t_arg **arg_list);

/*		INFILE		*/
t_infile	*ft_create_infile_list(t_data *data, t_token *cur_token);
void		ft_free_infiles(t_infile **infile_list);

/*		OUTFILE		*/
t_outfile	*ft_create_outfile_list(t_token *cur_token);
void		ft_free_outfiles(t_outfile **outfile_list);

/*	PARSER_UTILS	*/
t_token		*ft_extract_token(t_token *cur_token);
char		**ft_create_args_array(t_arg *arg_list);

/*		PARSER		*/
int			ft_parser(t_data *data);

#endif