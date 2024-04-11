/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvaudain <vvaudain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 14:37:20 by momrane           #+#    #+#             */
/*   Updated: 2024/04/11 14:07:46 by vvaudain         ###   ########.fr       */
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

extern int SIGNUM;

char	*ft_type_to_str(int type);

#endif