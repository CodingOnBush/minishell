/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:36:46 by momrane           #+#    #+#             */
/*   Updated: 2024/04/21 18:56:36 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*		ERRORS		*/
int		ft_pipe_at_end_error_check(t_token *list);
void	assign_error(t_token *token, int err_type);
void	ft_print_error(int errno);

/*	EXPAND_UTILS	*/
char	*ft_remove_quotes(char *str);
char	*ft_grab_str(char *str, char *limset);
char	*ft_grab_var_name(char *str);
char	*ft_get_expand(t_data *data, char *var_name, char *str);

/*		EXPAND		*/
char	*ft_get_expanded_str(t_data *data, char *str);
void	ft_expand(t_data *data, t_token **token_list);

/*		LEXER		*/
int		ft_lexer(t_data *data);

/*	TOKEN_CHECK		*/
int		ft_check_token_list(t_token *list);

/*		TOKEN		*/
t_token	*ft_new_token(char *new_str, int type, int pos, bool error);
void	ft_addlast_token(t_token **token_list, t_token *new_token);
t_token	*ft_create_token_list(char *line);

#endif