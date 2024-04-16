/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 07:10:20 by allblue           #+#    #+#             */
/*   Updated: 2024/04/16 16:17:20 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_get_path(t_env *env_list, t_arg *lst)
{
	char	*path;
	char	*tmp;

	(void)env_list;
	if (lst && lst->next != NULL && lst->token_type == WORD)
		return (printf("cd: too many arguments\n"), NULL);
	path = lst->value;
	if (ft_strncmp(path, "~", 1) == 0)
	{
		tmp = getenv("HOME");
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, path + 1);
		if (!path)
			return (free(tmp), perror("ft_strjoin"), NULL);
	}
	else if (ft_strncmp(path, "-", ft_strlen(path)) == 0)
	{
		path = getenv("OLDPWD");
		if (!path)
			return (printf("cd: OLDPWD not set\n"), NULL);
	}
	return (path);
}

int	ft_cd(t_env *env_list, t_arg *lst)
{
	char	*path;

	if (!lst || !lst->value || !ft_iscd(lst->value))
		return (printf("ft_cd: error"), FAIL);
	if (lst->next == NULL)
		path = getenv("HOME");
	else
		path = ft_get_path(env_list, lst->next);
	if (path)
	{
		if (chdir(path) == -1)
		{
			perror(path);
			return (FAIL);
		}
	}
	return (0);
}
