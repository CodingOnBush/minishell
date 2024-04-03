/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:46:05 by momrane           #+#    #+#             */
/*   Updated: 2024/04/03 17:37:11 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_pwd(t_arg *arg_list)
{
	char	*cwd;

	cwd = ft_getcwd();
	if (cwd == NULL)
	{
		perror("getcwd");
		return ;
	}
	printf("%s\n", cwd);
	free(cwd);
}

int	ft_exec_builtin(t_data *data, t_cmd *cmd)
{
	int	len;

	len = ft_strlen(cmd->arg_list->value);
	if (ft_strncmp(cmd->arg_list->value, "pwd", len) == 0)
		ft_pwd(cmd->arg_list->next);
	else
		printf("to be continued...\n");
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

void	ft_print_env(char **env)
{
	int	i;

	i = 0;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

int	ft_change_dir(char *path)
{
	// char	*new_path;

	// if (path == NULL)
	// {
	// 	new_path = ft_getenv("HOME");
	// 	if (new_path == NULL)
	// 	{
	// 		ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	// 		return (FAIL);
	// 	}
	// 	return (chdir(new_path));
	// }
	return (SUCCESS);
}
