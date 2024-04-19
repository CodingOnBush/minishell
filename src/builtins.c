/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:46:05 by momrane           #+#    #+#             */
/*   Updated: 2024/04/19 11:26:11 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static int	ft_pwd(t_data *data, t_cmd *cmd)
{
	char	*cwd;
	int		fd;

	if (!cmd || !cmd->arg_list || !cmd->arg_list->value)
		return (1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror(cmd->arg_list->value), 1);
	fd = ft_get_fd_out(data, cmd);
	ft_putstr_fd(cwd, fd);
	ft_putstr_fd("\n", fd);
	free(cwd);
	close(fd);
	return (0);
}

static int	ft_print_env_list(t_data *data, t_cmd *cmd)
{
	t_env	*env_list;
	int		fd;

	if (!data)
		return (1);
	env_list = data->env_list;
	fd = ft_get_fd_out(data, cmd);
	while (env_list)
	{
		ft_putstr_fd(env_list->key, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(env_list->value, fd);
		ft_putstr_fd("\n", fd);
		env_list = env_list->next;
	}
	return (0);
}

static int	ft_unset(t_data *data, t_arg *arg_list)
{
	if (!data || !arg_list || !arg_list->value)
		return (FAIL);
	if (arg_list->next == NULL)
		return (0);
	printf("arg_list->value = %s\n", arg_list->value);
	printf("arg_list->next->value = %s\n", arg_list->next->value);
	(void)data;
	(void)arg_list;
	// USE EXPORT.C FUNCTIONS
	// si aucun argument apres unset que faire ?
	// si plusieurs arguments apres unset que faire ?
	// si un seul argument apres unset recup key
	// supprimer key dans env_list
	// si key n'existe pas dans env_list ne rien faire
	// un fois que c'est supprimé dans env_list mettre a jour env en freeant l'ancien env pour le remplacer par le nouveau
	return (0);
}

int	ft_exec_builtin(t_data *data, t_cmd *cmd)
{
	if (ft_cmdcmp(cmd, "pwd") == YES)
		return (ft_pwd(data, cmd));
	if (ft_cmdcmp(cmd, "cd") == YES)
		return (ft_cd(data->env_list, cmd));
	if (ft_cmdcmp(cmd, "echo") == YES)
		return (ft_echo(data, cmd));
	if (ft_cmdcmp(cmd, "env") == YES)
		return (ft_print_env_list(data, cmd));
	if (ft_cmdcmp(cmd, ":") == YES || ft_cmdcmp(cmd, "!") == YES)
		return (0);
	if (ft_cmdcmp(cmd, "export") == YES)
		return (ft_export(data, cmd));
	if (ft_cmdcmp(cmd, "unset") == YES)
		return (ft_unset(data, cmd->arg_list));
	if (ft_cmdcmp(cmd, "exit") == YES)
		return (ft_exit(data, cmd->arg_list));
	return (SUCCESS);
}
