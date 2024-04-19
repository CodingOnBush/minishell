/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 19:48:28 by momrane           #+#    #+#             */
/*   Updated: 2024/04/19 15:33:48 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	ft_add_new_env(t_env **env_list, t_env *new)
{
	t_env	*tmp;

	if (!new)
		return ;
	if (!*env_list)
	{
		*env_list = new;
		return ;
	}
	tmp = *env_list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

char	*ft_getenv(t_env *env_list, char *key)
{
	t_env	*tmp;

	tmp = env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
			return (ft_strdup(tmp->value));
		tmp = tmp->next;
	}
	return (NULL);
}

void	ft_remove_env(t_env **env_list, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env_list;
	prev = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env_list = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

int	ft_update_var(t_env **env_list, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env_list;
	while (tmp)
	{
		if (ft_strncmp(tmp->key, key, ft_strlen(key)) == 0)
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return (SUCCESS);
		}
		tmp = tmp->next;
	}
	return (FAIL);
}

int	ft_add_new_env_var(t_env **env_list, char *key, char *value)
{
	t_env	*new;

	new = ft_create_new_var(key, value);
	if (!new)
		return (FAIL);
	ft_add_new_env(env_list, new);
	return (SUCCESS);
}

char	*ft_strjoin_key_value(char *key, char *value)
{
	char	*res;
	char	*tmp;

	tmp = ft_strjoin(key, "=");
	res = ft_strjoin(tmp, value);
	free(tmp);
	return (res);
}

char	*ft_extract_key(char*str)
{
	int		i;
	char	*res;

	if (ft_strchr(str, '=') == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	res = (char *)malloc(sizeof(char) * (i + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		res[i] = str[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_extract_value(char *str)
{
	int		i;
	int		j;
	char	*res;

	if (ft_strchr(str, '=') == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '\0')
		return (NULL);
	i++;
	j = 0;
	while (str[i + j])
		j++;
	res = (char *)malloc(sizeof(char) * (j + 1));
	if (!res)
		return (NULL);
	j = 0;
	while (str[i + j])
	{
		res[j] = str[i + j];
		j++;
	}
	res[j] = '\0';
	return (res);
}

void	ft_add_new_env_in_list(t_env **env_list, char *key, char *value)
{
	t_env	*new_var;

	new_var = ft_create_new_var(key, value);
	if (!new_var)
	{
		ft_free_env_list(env_list);
		*env_list = NULL;
		return ;
	}
	ft_add_new_env(env_list, new_var);
}

static int	ft_isvalid_varname(char *varname)
{
	int		i;

	i = 0;
	if (!varname || !varname[0] || ft_isdigit(varname[0]))
		return (NO);
	while (varname[i])
	{
		if (!ft_isalnum(varname[i]) && varname[i] != '_')
			return (NO);
		i++;
	}
	return (YES);
}

static int	ft_print_export(t_data *data, t_cmd *cmd)
{
	t_env	*env_list;
	int		fd;

	if (!data)
		return (1);
	env_list = data->env_list;
	fd = ft_get_fd_out(data, cmd);
	while (env_list)
	{
		ft_putstr_fd("export ", fd);
		ft_putstr_fd(env_list->key, fd);
		ft_putstr_fd("=", fd);
		ft_putstr_fd(env_list->value, fd);
		ft_putstr_fd("\n", fd);
		env_list = env_list->next;
	}
	return (0);
}

int	ft_export(t_data *data, t_cmd *cmd)
{
	t_arg	*arg_list;

	arg_list = cmd->arg_list;
	if (!data || !cmd || !arg_list || !arg_list->value)
		return (FAIL);
	if (arg_list->next == NULL)
		return (ft_putstr_fd("minishell : unspecified behaviour\n", 2), 1);
	
	// printf("arg_list->value = %s\n", arg_list->value);
	// printf("arg_list->next->value = %s\n", arg_list->next->value);
	// si plusieurs arguments apres export que faire ?
	// si un seul argument apres export recup key et value
	// ajouter key et value dans env_list
	// si key existe deja dans env_list update value
	// si key n'existe pas dans env_list ajouter key et value
	// si key est vide ou contient un = que faire ?
	// un fois que c'est ajouté dans env_list mettre a jour env en freeant l'ancien env pour le remplacer par le nouveau
	return (0);
}
