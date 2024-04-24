/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 10:57:23 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/24 13:00:46 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*on veut parcourir la token list de la commande pour trouver les redirections
POUR LES OUTFILES:
- on veut donc recuperer le dernier outfile de la liste d'outfile tout en verifiant qu'il n'y ait pas d'erreur de permission avant
- on veut ensuite ouvrir le fichier en fonction de l'append et du truncate
- on veut retourner le fd correspondant

POUR LES INFILES:
- on veut recuperer le dernier infile de la liste d'infile tout en verifiant qu'il n'y a pas d'erreur de permission avant ou de fichier inexistant
- on veut ensuite ouvrir le fichier en lecture seule
- on veut retourner le fd correspondant

Il y a plus de contraintes que ce que l'on pensait sur les outf et ce qui differe est aussi que l'on veut
parcourir la commande dans le sens de lecture.

Le but est que ces fonctions n'exit pas afin que l'on puisse les utiliser que l'on soit dans un enfant ou non.

Creer une struct pour renvoyer les bonnes redirections si pas d'erreurs.
*/

static bool	ft_get_open_mode(t_cmd *cmd, char *filename)
{
	t_outfile	*cur_outf;

	cur_outf = cmd->outfile_list;
	while (cur_outf != NULL)
	{
		if (ft_strcmp(cur_outf->filename, filename) == 0)
			return (cur_outf->append);
		cur_outf = cur_outf->next;
	}
	return (true);
}

t_redir	*ft_get_redirs(t_data *data, t_cmd *cmd)
{
	t_token		*cur;
	t_redir		*redir;
	bool		is_append;

	is_append = false;
	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (NULL);
	redir->fd_in = STDIN_FILENO;
	redir->fd_out = STDOUT_FILENO;
	redir->infile = NULL;
	redir->outfile = NULL;
	cur = cmd->token_list;
	if (!cur)
		return (NULL);
	while (cur != NULL)
	{
		if (cur->is_inf == YES)
		{
			if (access(cur->value, F_OK | R_OK) == 0)
				redir->infile = cur->value;
			else
			{
				// permission denied or file does not exist
				perror(redir->infile);
				data->exit_status = 1;
				free(redir);
				return (NULL);
			}
		}
		if (cur->is_outf == YES)
		{
			is_append = ft_get_open_mode(cmd, cur->value);
			if (access(cur->value, F_OK) == -1)
			{
				if (is_append == true)
					redir->fd_out = open(cur->value, O_CREAT | O_WRONLY | O_APPEND, 0644);
				else
					redir->fd_out = open(cur->value, O_CREAT | O_WRONLY | O_TRUNC, 0644);
				if (redir->fd_out == -1)
				{
					// open error
					data->exit_status = 1;
					perror(cur->value);
					free(redir);
					return (NULL);
				}
				if (redir->fd_out != -1 && redir->fd_out != STDOUT_FILENO)
					close(redir->fd_out);
			}
			else if (access(cur->value, W_OK) == -1)
			{
				// permission denied
				data->exit_status = 1;
				perror(cur->value);
				free(redir);
				return (NULL);
			}
			redir->outfile = cur->value;
		}
		cur = cur->next;
	}
	if (redir->infile)
	{
		redir->fd_in = open(redir->infile, O_RDONLY);
		if (redir->fd_in == -1)
		{
			data->exit_status = 1;
			// open error
			free(redir);
			perror(redir->infile);
			return (NULL);
		}
	}
	if (redir->outfile)
	{
		if (is_append == true)
			redir->fd_out = open(redir->outfile, O_CREAT | O_WRONLY | O_APPEND, 0644);
		else
			redir->fd_out = open(redir->outfile, O_CREAT | O_WRONLY | O_TRUNC, 0644);
		if (redir->fd_out == -1)
		{
			// open error
			data->exit_status = 1;
			close(redir->fd_in);
			perror(redir->outfile);
			free(redir);
			return (NULL);
		}
	}
	return (redir);
}
