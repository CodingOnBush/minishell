/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/03 14:33:06 by momrane           #+#    #+#             */
/*   Updated: 2024/05/01 17:15:46 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define PROMPT "\001\e[1;38;5;141m\002minishell\001\e[1;33m\002 > \001\033[0m\002"
# define MINISPELL "\001\e[1;38;5;141m\002[minispell]\001\e[1;33m\002 > \001\033[0m\002"

# define YES 1
# define NO 0
# define SKIP 2

# define SUCCESS 1
# define FAIL -1

# define DOUBLE_QUOTES '\"'
# define SINGLE_QUOTE '\''

# define HD 1
# define APPEND 2
# define PIPE 3
# define LT 4
# define RIGHT_TRUNC 5
# define WORD 6
# define NEWLINE_ERROR 7
# define QUOTES_ERROR 8
# define SINGLE_QUOTE_ERROR 9
# define DOUBLE_QUOTE_ERROR 10
# define QWORD 11
# define DOUBLE_PIPE_ERROR 12
# define LIM 13
# define PIPE_AT_END 14
# define HDEXEC 15

# define FDMAX 1024

#endif