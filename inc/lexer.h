/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:36:46 by momrane           #+#    #+#             */
/*   Updated: 2024/04/07 01:01:04 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*		CHECK		*/
int		ft_check_quote_error(char *line);
int		ft_double_pipe_detected(t_token *token);

/*		EXPAND		*/
void	ft_expand_words(t_token **token_list);

/*	EXPAND_UTILS	*/
char	*ft_remove_quotes(char *str);
char	*ft_grab_str(char *str, char *limset);
char	*ft_grab_var_name(char *str);
char	*ft_get_expand(char *var_name);

/*		ERRORS		*/
int		pipe_at_end_error_check(t_token *list);
void	assign_error(t_token *token, int err_type);
void	ft_print_error(int errno);

/*	TOKEN_CHECK		*/
int		check_token_list(t_token *list);
int		ft_check_pipe_error(t_token *token_list);

/*	TOKEN_UTILS		*/
void	ft_set_delimiter(t_token **token_list);
t_token	*ft_findlast_token(t_token *lst);
void	ft_addlast_token(t_token **token_list, t_token *new_token);
t_token	*ft_extract_token(t_token *cur_token);

/*		TOKEN		*/
t_token	*ft_new_token(char *new_str, int type, int pos, bool error);
t_token	*ft_create_token_list(char *line);

/*		LEXER		*/
int		ft_lexer(t_data *data);

#endif