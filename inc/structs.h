/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:34:23 by momrane           #+#    #+#             */
/*   Updated: 2024/04/06 16:52:12 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_infile
{
	char				*filename;
	char 				*delimiter;
	struct s_infile		*next;
}						t_infile;

typedef struct s_outfile
{
	char				*filename;
	bool				append;
	struct s_outfile	*next;
}						t_outfile;

typedef struct s_arg
{
	char				*value;
	struct s_arg		*next;
}						t_arg;

typedef struct s_token
{
	char				*str;
	int					type;
	bool				attributed;
	int					pos;
	bool				error;
	bool				pipe_at_end;
	int					err_type;
	struct s_token		*next;
}						t_token;

typedef struct s_cmd
{
	t_token				*token_list;
	t_arg				*arg_list;
	t_infile			*infile_list;
	t_outfile			*outfile_list;
	int					pos;
	char				**args;
	char				*cmd_path;
	struct s_cmd		*next;
}						t_cmd;

typedef struct s_data
{
	char				*line;
	char				**env;
	t_cmd				*cmd_list;
	t_token				*token_list;
	int					cmd_nb;
	int					hdnum;
	int					*fd_hd;
	char				**hd_files;
	int					*ids;
	int					**pipe_ends;
	char				**path_list;
	char				*join_path;
	int					step;
	struct sigaction	sigint_action;
	struct sigaction	sigquit_action;
}						t_data;

#endif