/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:46:05 by momrane           #+#    #+#             */
/*   Updated: 2024/04/16 16:15:32 by allblue          ###   ########.fr       */
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

static void	ft_print_env(t_env *env_list)
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
		return (ft_print_env(data->env_list), 0);
	if (ft_strncmp(cmd->arg_list->value, ":", len) == 0)
		return (0);
	if (ft_strncmp(cmd->arg_list->value, "!", len) == 0)
		return (1);
	return (SUCCESS);
}
