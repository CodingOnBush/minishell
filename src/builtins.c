/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:46:05 by momrane           #+#    #+#             */
/*   Updated: 2024/04/18 12:02:34 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_getcwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 1024);
	if (cwd == NULL)
	{
		perror("getcwd");
		return (NULL);
	}
	return (cwd);
}

static void	ft_print_env_list(t_env *env_list)
{
	while (env_list)
	{
		printf("%s=%s\n", env_list->key, env_list->value);
		env_list = env_list->next;
	}
}

static int	ft_pwd(t_env *env_list, t_arg *arg_list)
{
	char	*cwd;

	(void)env_list;
	cwd = ft_getcwd();
	if (cwd == NULL)
	{
		perror(arg_list->value);
		return (FAIL);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (0);
}

static int	ft_export(t_data *data, t_arg *arg_list)
{
	if (!data || !arg_list || !arg_list->value)
		return (FAIL);
	(void)data;
	(void)arg_list;
	// USE EXPORT.C FUNCTIONS
	// si aucun argument apres export que faire ?
	// si plusieurs arguments apres export que faire ?
	// si un seul argument apres export recup key et value
	// ajouter key et value dans env_list
	// si key existe deja dans env_list update value
	// si key n'existe pas dans env_list ajouter key et value
	// si key est vide ou contient un = que faire ?
	// un fois que c'est ajouté dans env_list mettre a jour env en freeant l'ancien env pour le remplacer par le nouveau
	return (0);
}

static int	ft_unset(t_data *data, t_arg *arg_list)
{
	if (!data || !arg_list || !arg_list->value)
		return (FAIL);
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
	int	len;

	if (!cmd->arg_list)
		return (SUCCESS);
	len = ft_strlen(cmd->arg_list->value);
	if (ft_strncmp(cmd->arg_list->value, "pwd", len) == 0)
		return (ft_pwd(data->env_list, cmd->arg_list->next));
	if (ft_iscd(cmd->arg_list->value))
		return (ft_cd(data->env_list, cmd->arg_list));
	if (ft_isecho(cmd->arg_list->value))
		return (ft_echo(cmd->arg_list));
	if (ft_strncmp(cmd->arg_list->value, "env", len) == 0)
		return (ft_print_env(data->env), 0);
	if (ft_strncmp(cmd->arg_list->value, ":", len) == 0)
		return (0);
	if (ft_strncmp(cmd->arg_list->value, "!", len) == 0)
		return (1);
	if (ft_strncmp(cmd->arg_list->value, "export", len) == 0)
		return (ft_export(data, cmd->arg_list));
	if (ft_strncmp(cmd->arg_list->value, "unset", len) == 0)
		return (ft_unset(data, cmd->arg_list));
	if (ft_strncmp(cmd->arg_list->value, "exit", len) == 0)
		return (ft_exit(data, cmd->arg_list));
	return (SUCCESS);
}
