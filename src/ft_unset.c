/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 23:56:03 by allblue           #+#    #+#             */
/*   Updated: 2024/04/20 00:43:10 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int	ft_unset(t_data *data, t_arg *arg_list)
{
	if (!data || !arg_list || !arg_list->value)
		return (FAIL);
	if (arg_list->next == NULL)
		return (0);
	printf("arg_list->value = %s\n", arg_list->value);
	printf("arg_list->next->value = %s\n", arg_list->next->value);
	(void)data;
	(void)arg_list;
	// USE EXPORT.C FUNCTIONS
	// si aucun argument apres unset que faire ?
	// si plusieurs arguments apres unset que faire ?
	// si un seul argument apres unset recup key
	// supprimer key dans env_list
	// si key n'existe pas dans env_list ne rien faire
	// un fois que c'est supprimé dans env_list mettre a jour env en freeant l'ancien env pour le remplacer par le nouveau
	return (0);
}
