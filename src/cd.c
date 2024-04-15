/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/15 07:10:20 by allblue           #+#    #+#             */
/*   Updated: 2024/04/15 07:32:47 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static char	*ft_get_path(t_arg *lst)
{
	char	*path;

	if (lst->next->next != NULL)
		return (printf("cd: too many arguments\n"), NULL);
	path = lst->value;
	return (path);
}

int	ft_cd(t_arg *lst)
{
	char	*path;

	if (!lst || !lst->value || !ft_iscd(lst->value))
		return (printf("ft_cd: stop"), FAIL);
	if (lst->next == NULL)
		path = getenv("HOME");
	else
		path = ft_get_path(lst->next);
	if (path)
	{
		if (chdir(path) == -1)
			return (perror(path), FAIL);
		// update PWD and OLDPWD
	}
	return (0);
}
