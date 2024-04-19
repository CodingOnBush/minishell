/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 07:10:20 by allblue           #+#    #+#             */
/*   Updated: 2024/04/19 11:55:49 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_get_path(t_env *env_list, t_arg *lst)
{
	char	*path;
	char	*tmp;

	(void)env_list;
	if (lst && lst->next != NULL && lst->token_type == WORD)
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), NULL);
	path = lst->value;
	if (ft_strncmp(path, "~", 1) == 0)
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

int	ft_cd(t_env *env_list, t_arg *lst)
{
	char	*path;
	char	*cur_pwd;

	if (!lst || !lst->value || !ft_iscd(lst->value))
		return (printf("ft_cd: error"), 1);
	if (lst->next == NULL)
		path = ft_getenv(env_list, "HOME");
	else
		path = ft_get_path(env_list, lst->next);
	if (path)
	{
		cur_pwd = getcwd(NULL, 0);
		if (!cur_pwd)
			cur_pwd = path;
		if (chdir(path) == -1)
		{
			perror(path);
			return (1);
		}
		// printf("cur OLDPWD: %s\n", ft_getenv(env_list, "OLDPWD"));
		// printf("cur PWD: %s\n", ft_getenv(env_list, "PWD"));
		if (ft_update_var(&env_list, "OLDPWD", cur_pwd) == FAIL)
			ft_add_new_env_in_list(&env_list, "OLDPWD", cur_pwd);
		free(cur_pwd);
		cur_pwd = getcwd(NULL, 0);
		if (ft_update_var(&env_list, "PWD", cur_pwd) == FAIL)
			ft_add_new_env_in_list(&env_list, "PWD", cur_pwd);
		free(cur_pwd);
		// printf("new OLDPWD: %s\n", ft_getenv(env_list, "OLDPWD"));
		// printf("new PWD: %s\n", ft_getenv(env_list, "PWD"));
	}
	free(path);
	return (0);
}
