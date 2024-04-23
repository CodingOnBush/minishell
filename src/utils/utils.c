/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/12 16:29:20 by momrane           #+#    #+#             */
/*   Updated: 2024/04/22 17:47:25 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_isappend(char *str)
{
	if (!str)
		return (NO);
	if (str[0] == '>' && str[1] && str[1] == '>')
		return (YES);
	return (NO);
}

static int	ft_isheredoc(char *str)
{
	if (!str)
		return (NO);
	if (str[0] == '<' && str[1] && str[1] == '<')
		return (YES);
	return (NO);
}

int	ft_isop(char *str)
{
	int	len;

	len = ft_strlen(str);
	if (!str)
		return (NO);
	if (ft_strncmp(str, ">>", len) == 0)
		return (YES);
	if (ft_strncmp(str, "<<", len) == 0)
		return (YES);
	if (ft_strncmp(str, ">", len) == 0)
		return (YES);
	if (ft_strncmp(str, "<", len) == 0)
		return (YES);
	return (NO);
}

int  ft_get_type(char *str)
{
	if (*str == '|')
		return (PIPE);
	if (ft_isheredoc(str) == YES)
		return (HERE_DOC);
	if (ft_isappend(str) == YES)
		return (APPEND);
	if (*str == '<')
		return (LEFT_TRUNC);
	if (*str == '>')
		return (RIGHT_TRUNC);
	return (WORD);
}

int	ft_isoperator(char *str)
{
	if (!str)
		return (NO);
	if (ft_isappend(str) || ft_isheredoc(str))
		return (2);
	if (ft_strchr("|><", *str) != NULL)
		return (1);
	return (NO);
}

char	*ft_strndup(char *s, int n)
{
	char	*res;
	int		len;
	int		i;

	len = ft_strlen(s);
	if (len == 0)
		return (NULL);
	res = (char *)malloc(sizeof(char) * (n + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (s[i] != '\0' && i < n)
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_super_strjoin(char *new_str, char *toadd)
{
	int		new_str_len;
	int		toadd_len;
	int		new_len;
	char	*join;

	if (new_str == NULL && toadd == NULL)
		return (NULL);
	new_str_len = ft_strlen(new_str);
	toadd_len = ft_strlen(toadd);
	new_len = new_str_len + toadd_len;
	join = malloc(sizeof(char) * (new_len + 1));
	if (!join)
		return (NULL);
	if (new_str != NULL)
		ft_strlcpy(join, new_str, new_str_len + 1);
	if (toadd)
		ft_strlcpy(join + new_str_len, toadd, toadd_len + 1);
	join[new_len] = '\0';
	if (new_str != NULL)
		free(new_str);
	if (toadd != NULL)
		free(toadd);
	return (join);
}

int	ft_is_space(char c)
{
	if ((c >= 9 && c <= 13) || c == ' ')
		return (YES);
	return (NO);
}

int	ft_isquote(char c)
{
	if (c == DOUBLE_QUOTES || c == SINGLE_QUOTE)
		return (YES);
	return (NO);
}

int	ft_is_in_var(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (YES);
	return (NO);
}

int	is_exit_builtin(t_data *data)
{
	t_cmd	*cmd;

	if (!data || !data->cmd_list)
		return (NO);
	cmd = data->cmd_list;
	if (!cmd->args)
		return (NO);
	while (cmd)
	{
		if (ft_strncmp(cmd->args[0], "exit", ft_strlen("exit")) == 0)
			return (YES);
		cmd = cmd->next;
	}
	return (NO);
}

int	ft_strcmp(char *s1, char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;
	int				i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}