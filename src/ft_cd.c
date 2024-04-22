/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 07:10:20 by allblue           #+#    #+#             */
/*   Updated: 2024/04/22 11:39:03 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_get_path(t_env *env_list, t_arg *lst)
{
	char	*path;
	char	*tmp;

	// if (!lst)
	// 	return (NULL);
	if (lst && lst->next != NULL && lst->token_type == WORD)
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), NULL);
	path = lst->value;
	if (!path)
	{
		tmp = ft_getenv(env_list, "HOME");
		if (!tmp)
			return (ft_putstr_fd("cd: HOME not set\n", 2), NULL);
		path = tmp;
	}
	else if (ft_strncmp(path, "~", 1) == 0)
	{
		tmp = ft_getenv(env_list, "HOME");
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, path + 1);
		if (!path)
			return (free(tmp), perror("ft_strjoin"), NULL);
		free(tmp);
	}
	else if (ft_strncmp(path, "-", ft_strlen(path)) == 0)
	{
		path = ft_getenv(env_list, "OLDPWD");
		if (!path)
			return (ft_putstr_fd("cd: OLDPWD not set\n", 2), NULL);
	}
	else if (path && path[0] == '.' && path[1] && path[1] == '.')
	{
		tmp = ft_getenv(env_list, "PWD");
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, "/");
		if (!path)
			return (free(tmp), perror("ft_strjoin"), NULL);
		tmp = ft_strjoin(path, lst->value);
		if (!tmp)
			return (free(path), perror("ft_strjoin"), NULL);
		free(path);
		path = tmp;
	}
	else if (path && (path[0] != '/' || path[0] != '.'))
	{
		tmp = ft_getenv(env_list, "PWD");
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, "/");
		if (!path)
			return (free(tmp), perror("ft_strjoin"), NULL);
		free(tmp);
		tmp = ft_strjoin(path, lst->value);
		if (!tmp)
			return (free(path), perror("ft_strjoin"), NULL);
		free(path);
		path = tmp;
	}
	return (path);
}

int	ft_cd(t_env *env_list, t_cmd *cmd)
{
	t_arg	*lst;
	char	*path;
	char	*cur_pwd;

	lst = cmd->arg_list;
	if (!lst || !lst->value || ft_strcmp(lst->value, "cd") != 0)
		return (printf("ft_cd: error"), 1);
	if (lst && lst->next == NULL)
	{
		path = ft_getenv(env_list, "HOME");
		if (!path)
			return (ft_putstr_fd("cd: HOME not set\n", 2), 1);
	}
	else
	{
		path = ft_get_path(env_list, lst->next);
		if (!path)
			return (1);
	}
	cur_pwd = getcwd(NULL, 0);
	if (!cur_pwd)
		cur_pwd = path;
	if (chdir(path) == -1)
		return (perror("minishell : "), perror(path), 1);
	ft_setenv(&env_list, "OLDPWD", cur_pwd);
	free(cur_pwd);
	cur_pwd = getcwd(NULL, 0);
	ft_setenv(&env_list, "PWD", cur_pwd);
	free(cur_pwd);
	free(path);
	return (0);
}
