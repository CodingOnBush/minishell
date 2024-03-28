/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:46:05 by momrane           #+#    #+#             */
/*   Updated: 2024/03/28 12:59:12 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

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
