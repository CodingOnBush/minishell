/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 12:59:52 by momrane           #+#    #+#             */
/*   Updated: 2024/04/29 14:09:08 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
void	ft_add_new_exp(t_env **exp_list, t_env *new);
Il me faut une fonction ajoute un nouveau t_env dans une liste
de t_env.
Il faut que ce nouveau t_env soit ajoute de maniere a respecter
l'ordre alphabetique des cles.
*/

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
