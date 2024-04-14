/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:46:05 by momrane           #+#    #+#             */
/*   Updated: 2024/04/14 15:59:31 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_print_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

int	ft_pwd(t_arg *arg_list)
{
	char	*cwd;

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

	len = ft_strlen(cmd->arg_list->value);
	if (ft_strncmp(cmd->arg_list->value, "pwd", len) == 0)
		return (ft_pwd(cmd->arg_list->next));
	if (ft_strncmp(cmd->arg_list->value, "cd", len) == 0)
		return (ft_change_dir(cmd));
	if (ft_strncmp(cmd->arg_list->value, "echo", len) == 0)
		return (ft_echo(cmd->arg_list));
	if (ft_strncmp(cmd->arg_list->value, "env", len) == 0)
		return (ft_print_env(data->env), 0);
	if (ft_strncmp(cmd->arg_list->value, ":", len) == 0)
		return (0);
	if (ft_strncmp(cmd->arg_list->value, "!", len) == 0)
		return (1);
	return (SUCCESS);
}

char	*ft_getcwd(void)
{
	char	*cwd;

	cwd = malloc(1024 * sizeof(char));
	if (!cwd)
		return (NULL);
	getcwd(cwd, 1024);
	return (cwd);
}

int	ft_change_dir(t_cmd *cmd)
{
	char	*path;
	t_arg	*arg_list;

	path = NULL;
	arg_list = cmd->arg_list;
	if (!cmd || !arg_list)
		return (FAIL);
	if (arg_list->next == NULL)
	{
		path = getenv("HOME");
		if (!path)
			return (FAIL);// no home so no cd and no error
	}
	else
		path = arg_list->next->value;
	if (arg_list->next->next != NULL)
	{
		printf("cd: too many arguments\n");
		return (FAIL);
	}
	if (chdir(path) == -1)
	{
		perror(path);
		return (FAIL);
	}
	return (0);
}
