/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 07:10:20 by allblue           #+#    #+#             */
/*   Updated: 2024/04/26 12:56:01 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static char	*ft_get_path(t_arg *lst, t_env *env_list)
{
	char	*path;
	char	*key;

	path = NULL;
	if (lst && lst->next && ft_strcmp(lst->next->value, "~") == 0)
	{
		path = getenv("HOME");
		if (!path)
			return (NULL);
		return (ft_strdup(path));
	}
	else if (lst && lst->next == NULL)
	{
		key = ft_getkey(env_list, "HOME");
		if (!key)
			return (ft_strdup("."));
		path = ft_getenv(env_list, "HOME");
		printf("path: %s\n", path);
		if (!path)
			return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), NULL);
	}
	else if (lst && lst->next && ft_strcmp(lst->next->value, "-") == 0)
	{
		path = ft_getenv(env_list, "OLDPWD");
		printf("%s\n", path);
		return (path);
	}
	else if (lst && lst->next && ft_strcmp(lst->next->value, "--") == 0)
		path = ft_getenv(env_list, "OLDPWD");
	else if (lst && lst->next)
		path = ft_strdup(lst->next->value);
	return (path);
}

static int	ft_count_args(t_arg *lst)
{
	int	count;

	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

int	ft_cd(t_env *env_list, t_cmd *cmd)
{
	t_arg	*lst;
	char	*path;
	char	*wd;

	lst = cmd->arg_list;
	if (!lst || !lst->value)
		return (1);
	if (ft_count_args(lst) > 2)
		return (ft_putstr_fd("minishell: cd: too many arguments\n", 2), 1);
	if (lst && lst->next && ft_strncmp(lst->next->value, "---", 3) == 0)
		return (ft_putstr_fd("minishell: cd: --: invalid option\n", 2), 2);
	path = ft_get_path(lst, env_list);
	if (!path)
		return (1);
	wd = getcwd(NULL, 0);
	if (chdir(path) == -1)
		return (ft_putstr_fd("minishell : ", 2), perror(path), free(path),
			free(wd), 1);
	free(path);
	ft_setenv(&env_list, ft_strdup("OLDPWD"), ft_strdup(wd));
	free(wd);
	wd = getcwd(NULL, 0);
	ft_setenv(&env_list, ft_strdup("PWD"), ft_strdup(wd));
	free(wd);
	return (0);
}
