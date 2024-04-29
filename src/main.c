/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:32:05 by vvaudain          #+#    #+#             */
/*   Updated: 2024/04/29 10:31:33 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	g_signum;

static void	ft_wait_for_children(t_data *data)
{
	int	status;

	status = 0;
	if (!data->ids)
		return ;
	if (waitpid(data->ids[data->cmd_nb - 1], &status,
			0) == data->ids[data->cmd_nb - 1])
	{
		if (WIFEXITED(status))
			data->exit_status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status) != 0)
			data->exit_status = g_signum + 128;
		else
			data->exit_status = 0;
	}
}

// int	main(int ac, char **av, char **env)
// {
// 	t_data *const	data = ft_create_data(ac, av, env);
// 	int				s;

// 	if (!data || ac != 1)
// 		return (-1);
// 	while (1)
// 	{
// 		data->line = readline(MINISPELL);
// 		if (!data->line)
// 			break ;
// 		add_history(data->line);
// 		if (ft_lexer(data) == SUCCESS && ft_parser(data) == SUCCESS)
// 			ft_launch_exec(data);
// 		ft_wait_for_children(data);
// 		if (is_exit_builtin(data) == YES && data->exit_status != 1)
// 		{
// 			s = data->exit_status;
// 			ft_free_all(data);
// 			exit(s);
// 		}
// 		ft_reset_data(data);
// 	}
// 	if (isatty(STDIN_FILENO))
// 		write(2, "exit\n", 6);
// 	return (s = data->exit_status, rl_clear_history(), ft_free_all(data), s);
// }

int main(int argc, char **argv, char **env)
{
	t_data *const	data = ft_create_data(argc, argv, env);
	int				s;

	if (!data)
		return (-1);
	if (argc >= 3 && !ft_strncmp(argv[1], "-c", 3))
	{
		// data->line = readline(MINISPELL);
		data->line = ft_strdup(argv[2]);
		if (!data->line)
		{
			if (is_exit_builtin(data) == YES && data->exit_status != 1)
			{
				s = data->exit_status;
				ft_free_all(data);
				exit(s);
			}
			return (s = data->exit_status, rl_clear_history(), ft_free_all(data), s);
		}
		add_history(data->line);
		if (ft_lexer(data) == SUCCESS && ft_parser(data) == SUCCESS)
		ft_launch_exec(data);
		ft_wait_for_children(data);
		if (is_exit_builtin(data) == YES && data->exit_status != 1)
		{
			s = data->exit_status;
			ft_free_all(data);
			exit(s);
		}
		return (s = data->exit_status, rl_clear_history(), ft_free_all(data), s);
	}
	while (1)
	{
		data->line = readline(MINISPELL);
		if (!data->line)
		break ;
		add_history(data->line);
		if (ft_lexer(data) == SUCCESS && ft_parser(data) == SUCCESS)
		ft_launch_exec(data);
		ft_wait_for_children(data);
		if (is_exit_builtin(data) == YES && data->exit_status != 1)
		{
		s = data->exit_status;
		ft_free_all(data);
		exit(s);
		}
		ft_reset_data(data);
	}
	if (isatty(STDIN_FILENO))
		write(2, "exit\n", 6);
	return (s = data->exit_status, rl_clear_history(), ft_free_all(data), s);
}
