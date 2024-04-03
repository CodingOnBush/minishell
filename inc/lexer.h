/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:36:46 by momrane           #+#    #+#             */
/*   Updated: 2024/04/03 14:55:36 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

/*			CHECK			*/
int		ft_check_quote_error(char *line);
int 	ft_check_double_pipe(t_token *token);

/*			ERRORS			*/
int		pipe_at_end_error_check(t_token *list);
void	assign_error(t_token *token, int err_type);
void	ft_error_messages(int errno);

/*			EXPAND_UTILS	*/
char	*ft_remove_quotes(char *str);
char	*ft_grab_str(char *str, char *limset);
char	*ft_grab_var_name(char *str);
char	*ft_get_expand(char *var_name);

/*			EXPAND			*/
void	ft_expand(t_token **token_list);

/*			TOKEN_CHECK		*/
int		check_token_list(t_token **list);
int		ft_check_pipe_error(t_token *token_list);

/*			TOKEN_UTILS		*/
void	ft_detect_delimiter(t_token **token_list);
t_token	*ft_findlast_token(t_token *lst);
void	ft_addlast_token(t_token **token_list, t_token *new_token);
t_token	*ft_find_next_pipe(t_token *cur_token);

/*			TOKEN			*/
t_token	*ft_create_new_token(char *new_str, int type, int pos, bool error);
t_token	*ft_create_token_list(char *line);

#endif