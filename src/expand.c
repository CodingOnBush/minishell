/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: allblue <allblue@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 12:16:46 by vvaudain          #+#    #+#             */
/*   Updated: 2024/03/30 18:16:26 by allblue          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

char	*ft_super_strjoin(char *extended_str, char *toadd)
{
	char	*new_str;
	int		len;
	int		i;
	int		j;

	if (toadd == NULL)
		return (extended_str);
	len = ft_strlen(extended_str) + ft_strlen(toadd);
	new_str = malloc(sizeof(char) * (len + 1));
	if (!new_str)
		return (NULL);
	i = 0;
	while (i < ft_strlen(extended_str))
	{
		new_str[i] = extended_str[i];
		i++;
	}
	j = 0;
	while (i < len)
	{
		new_str[i] = toadd[j];
		i++;
		j++;
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*ft_simple_expand(char *str, int *step)
{
	char	*var_name;
	int		i;

	*step += 1;
	i = 0;
	if (!str || *str != '$')
		return (NULL);
	var_name = str;
	// var_name = ft_get_var_name(str);
	if (!var_name)
		return (ft_strdup("$"));
	*step += ft_strlen(var_name) + 1;
	return (getenv(var_name));
}

int	ft_step_to_next_var(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '$' && str[i] != DOUBLE_QUOTES)
		i++;
	return (i);
}

char	*ft_grab_str_until_next_var(char *str, int *step)
{
	int		len;
	char	*res;

	len = 0;
	while (str[len] && str[len] != '$' && str[len] != DOUBLE_QUOTES)
		len++;
	*step = 1;
	if (len == 0)
		return (NULL);
	res = ft_substr(str, 0, len);
	if (!res)
		return (NULL);
	*step = len;
	return (res);
}

char	*ft_expand_in_double_quotes(char *str)
{
	char	*expanded_str;
	char	*toadd;
	char	*tmp;
	int		step;

	step = 0;
	expanded_str = NULL;
	while (*str)
	{
		if (*str == '$')
			toadd = ft_simple_expand(str, &step);
		else
			toadd = ft_grab_str_until_next_var(str, &step);
		tmp = ft_super_strjoin(expanded_str, toadd);
		if (!tmp)
			return (NULL);
		free(expanded_str);
		expanded_str = tmp;
		str += step;
	}
	return (expanded_str);
}

int ft_strlen_util(char *str, char *limset)
{
	int i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] && ft_strchr(limset, str[i]) == NULL)
		i++;
	return (i);
}

char *ft_grab_str(char *str, char *limset)
{
	char    *grab;
	int     len;
	int		i;

	if (!str)
		return (NULL);
	len = ft_strlen_util(str, limset);
	if (len == 0)
		return (NULL);
	grab = malloc(sizeof(char) * (len + 1));
	if (!grab)
		return (NULL);
	ft_strlcpy(grab, str, len + 1);
	return (grab);
}

char	*ft_get_expanded_str(char *str)
{
	char	*expanded_str;
	char	*str_btw_quotes;
	char	*var_name;
	char	*toadd;
	char	*var_content;
	char	*tmp;
	int		len;
	int		i;
	int		j;
	int		step;

	i = 0;
	expanded_str = NULL;
	while (str[i])
	{
		if (str[i] == DOUBLE_QUOTES)
		{
			len = ft_strlen_util(&str[i], "\"");
			tmp = ft_substr(&str[i], i + 1, len - 1);
			tmp = ft_expand_in_double_quotes(tmp);
			expanded_str = ft_super_strjoin(expanded_str, tmp);
			i += len + 1;
		}
		else if (str[i] == SINGLE_QUOTE)
		{
			len = ft_strlen_util(&str[i], "\'");
			tmp = ft_substr(&str[i], i + 1, len - 1);
			expanded_str = ft_super_strjoin(expanded_str, tmp);
			i += len + 1;
		}
		else if (str[i] == '$')
		{
			tmp = ft_simple_expand(&str[i], &i);
			expanded_str = ft_super_strjoin(expanded_str, tmp);
		}
		else
		{
			tmp = ft_grab_str(str, "$\'\"");
			printf("tmp : %s\n", tmp);
			// expanded_str = ft_super_strjoin(expanded_str, tmp);
			i += ft_strlen_util(tmp, "$\'\"");
		}
	}
	return (expanded_str);
}

int	ft_expand(t_data *data)
{
	t_token	*token;
	char	*expanded_str;

	token = data->token_list;
	if (token == NULL)
		return (SUCCESS);
	while (token)
	{
		if (token->type == WORD)
		{
			expanded_str = ft_get_expanded_str(token->str);
			if (!expanded_str)
				return (FAIL);
			printf("->[%s]\n", expanded_str);
			free(token->str);
			token->str = expanded_str;
		}
		token = token->next;
	}
	return (SUCCESS);
}
