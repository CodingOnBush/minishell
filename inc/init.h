/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:38:17 by momrane           #+#    #+#             */
/*   Updated: 2024/04/03 14:49:29 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

/*		DATA		*/
t_data	*ft_create_data(int ac, char **av, char **env);
int		ft_finish_init_data(t_data *data);

/*		SIGNALS		*/
void	ft_setup_signals(t_data *data);

#endif