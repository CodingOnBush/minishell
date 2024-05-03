/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:34:23 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 11:24:38 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_infile
{
	char				*filename;
	char				*delimiter;
	int					hd_num;
	bool				to_expand;
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
	int					token_type;
	struct s_arg		*next;
}						t_arg;

typedef struct s_redir
{
	int					fd_in;
	int					fd_out;
	char				*infile;
	char				*outfile;
}						t_redir;

typedef struct s_token
{
	char				*value;
	int					type;
	bool				attributed;
	int					pos;
	bool				error;
	bool				pipe_at_end;
	int					err_type;
	bool				is_inf;
	bool				is_outf;
	bool				to_expand;
	char				*heredoc_file;
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

typedef struct s_env
{
	char				*base;
	char				*key;
	char				*value;
	struct s_env		*next;
}						t_env;

typedef struct s_data
{
	char				*line;
	t_cmd				*cmd_list;
	t_token				*token_list;
	int					cmd_nb;
	int					hdnum;
	int					*fd_hd;
	char				**hd_files;
	int					*ids;
	int					**pipe_ends;
	char				*join_path;
	int					step;
	t_env				*env_list;
	t_env				*exp_list;
	struct sigaction	act_interupt;
	struct sigaction	act_quit;
	int					exit_status;
	int					exit_builtin;
	int					hd_pos;
}						t_data;

#endif