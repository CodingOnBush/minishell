/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:46:05 by momrane           #+#    #+#             */
/*   Updated: 2024/04/15 08:49:12 by allblue          ###   ########.fr       */
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

	if (!cmd->arg_list)
		return (SUCCESS);
	len = ft_strlen(cmd->arg_list->value);
	if (ft_strncmp(cmd->arg_list->value, "pwd", len) == 0)
		return (ft_pwd(cmd->arg_list->next));
	if (ft_iscd(cmd->arg_list->value))
		return (ft_cd(cmd->arg_list));
	if (ft_isecho(cmd->arg_list->value))
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

