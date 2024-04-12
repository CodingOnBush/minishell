/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:20 by momrane           #+#    #+#             */
/*   Updated: 2024/04/12 16:47:18 by vvaudain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
#define MINISHELL_H

#include "includes.h"
#include "defines.h"
#include "structs.h"

#include "init.h"
#include "lexer.h"
#include "parser.h"
#include "exec.h"

extern int g_signum;

char	*ft_type_to_str(int type);

#endif