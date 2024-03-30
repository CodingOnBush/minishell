/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 15:38:01 by momrane           #+#    #+#             */
/*   Updated: 2024/03/30 17:54:07 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_start_exec(t_data *data)
{
    char    *str;
    // int     res;
    char    *grab;

    str = ft_strdup("1234");
    // res = ft_strlen_util(str, "$");
	// printf("=======\n%d\n=======\n", res);
    grab = ft_grab_str(str, "$\'");
    printf("grab : %s\n", grab);
}
