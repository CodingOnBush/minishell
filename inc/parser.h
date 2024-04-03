/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:50:01 by momrane           #+#    #+#             */
/*   Updated: 2024/04/03 17:34:24 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

/* =========================== */
/* ===========TODO============ */
/* refactor parser & cmd list  */
/* =========================== */
/* =========================== */

/*		ARGS		*/
t_arg	*create_new_arg(char *value);
void	add_new_arg(t_arg **head, t_arg *new_arg);
int	ft_get_arg_nbr(t_arg *arg_list);
char	**ft_arg_list_to_array(t_arg *arg_list);

/*		CMD_UTILS	*/
t_cmd	*ft_create_cmd(t_token *cur_token, int pos);
t_cmd	*ft_create_cmd_list(t_token *token_list);
void	ft_add_new_cmd(t_cmd **cmd_list, t_cmd *new_cmd);
t_cmd	*ft_create_new_cmd(t_token *cur_token, int pos);

/*		INFILE		*/
t_infile	*ft_create_new_infile(char *str, int type);
void	ft_add_infile(t_infile **infile_list, t_infile *new_infile);

/*		OUTFILE		*/
t_outfile	*ft_create_new_outfile(char *filename, int type);
void	ft_add_outfile(t_outfile **outfile_list, t_outfile *new_outfile);

/*		PARSER		*/
int	parse_infiles(t_cmd *new_cmd, t_token *token);
int	parse_outfiles(t_cmd *new_cmd, t_token *token);
t_token	*ft_extract_token(t_token *token_list);
t_token	*ft_get_last_redir(t_token *cur_token);
int	parse_commands(t_cmd *new_cmd, t_token *token);

#endif