/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:01:55 by momrane           #+#    #+#             */
/*   Updated: 2024/04/30 18:06:53 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"


void	ft_add_new_exp(t_env **exp_list, t_env *new)
{
	t_env	*cur;
	t_env	*prev;

	if (!*exp_list)
	{
		*exp_list = new;
		return ;
	}
	cur = *exp_list;
	prev = NULL;
	while (cur && ft_strcmp(cur->key, new->key) < 0)
	{
		prev = cur;
		cur = cur->next;
	}
	if (!prev)
	{
		new->next = *exp_list;
		*exp_list = new;
	}
	else
	{
		prev->next = new;
		new->next = cur;
	}
}

t_env	*ft_create_explist(char **env)
{
	t_env	*exp_list;
	t_env	*new;
	int		i;

	exp_list = NULL;
	i = 0;
	while (env[i])
	{
		new = ft_str_to_env(env[i]);
		if (new)
			ft_add_new_exp(&exp_list, new);
		i++;
	}
	return (exp_list);
}

void	ft_print_exports_var(t_data *data)
{
	t_env	*exp_list;

	if (!data)
		return ;
	exp_list = data->exp_list;
	while (exp_list)
	{
		ft_putstr_fd("export ", 1);
		ft_putstr_fd(exp_list->key, 1);
		ft_putstr_fd("=", 1);
		ft_putstr_fd(exp_list->value, 1);
		ft_putstr_fd("\n", 1);
		exp_list = exp_list->next;
	}
}
