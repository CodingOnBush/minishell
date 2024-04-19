/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 16:30:56 by momrane           #+#    #+#             */
/*   Updated: 2024/04/20 01:08:01 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signum = signum;
		ft_putstr_fd("\n", STDOUT_FILENO);
		// rl_replace_line("", STDIN_FILENO);// "ls |\n>"
		rl_on_new_line();
		// rl_redisplay();
	}
}

static void	ft_setup_signals(t_data *data)
{
	data->act_interupt.sa_handler = ft_handler;
	data->act_quit.sa_handler = SIG_IGN;
	sigemptyset(&data->act_interupt.sa_mask);
	sigemptyset(&data->act_quit.sa_mask);
	data->act_interupt.sa_flags = 0;//to have a ft_handler with only one arg (signum)
	data->act_quit.sa_flags = 0;
	sigaction(SIGINT, &data->act_interupt, NULL);
	sigaction(SIGact_quit, &data->act_quit, NULL);
}

static t_env	*ft_line_to_env(char *line)
{
	t_env	*new_env;
	char	*equal;

	equal = ft_strchr(line, '=');
	if (!equal)
		return (NULL);
	new_env = malloc(sizeof(t_env));
	if (!new_env)
		return (NULL);
	new_env->key = ft_substr(line, 0, equal - line);
	if (!new_env->key)
		return (free(new_env), NULL);
	new_env->value = ft_strdup(equal + 1);
	if (!new_env->value)
		return (free(new_env->key), free(new_env), NULL);
	new_env->next = NULL;
	return (new_env);
}

static t_env	*ft_create_envlist(char **env)
{
	t_env	*res;
	t_env	*new;
	int		i;

	res = NULL;
	i = 0;
	while (env[i])
	{
		new = ft_line_to_env(env[i]);
		if (!new)
			return (NULL);
		ft_add_new_env(&res, new);
		i++;
	}
	return (res);
}

t_data *const	ft_create_data(int ac, char **av, char **env)
{
	t_data *const	data = malloc(sizeof(t_data));

	(void)ac;
	(void)av;
	if (!data)
		return (NULL);
	ft_memset(data, 0, sizeof(t_data));
	data->env = env;// to remove
	data->line = NULL;
	data->cmd_list = NULL;
	data->token_list = NULL;
	data->cmd_nb = 0;
	data->hdnum = 0;
	data->fd_hd = NULL;
	data->hd_files = NULL;
	data->ids = NULL;
	data->pipe_ends = NULL;
	data->join_path = NULL;
	data->step = 0;
	data->env_list = ft_create_envlist(env);
	data->hd_pos = -1;
	data->exit_status = 0;
	data->exit_builtin = NO;
	ft_setup_signals(data);
	return (data);
}
