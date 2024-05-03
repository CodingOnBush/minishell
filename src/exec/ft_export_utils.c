/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 18:01:55 by momrane           #+#    #+#             */
/*   Updated: 2024/05/02 11:00:56 by momrane          ###   ########.fr       */
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

t_env	*ft_create_default_exp(void)
{
	t_env	*new;
	t_env	*res;

	res = NULL;
	new = ft_create_new_env("PWD=", "PWD", getcwd(NULL, 0));
	if (!new)
		return (ft_free_env_list(&res), NULL);
	ft_add_new_exp(&res, new);
	new = ft_create_new_env("SHLVL=", "SHLVL", "1");
	if (!new)
		return (ft_free_env_list(&res), NULL);
	ft_add_new_exp(&res, new);
	new = ft_create_new_env(NULL, "OLDPWD", NULL);
	if (!new)
		return (ft_free_env_list(&res), NULL);
	ft_add_new_exp(&res, new);
	return (res);
}

t_env	*ft_create_explist(char **env)
{
	t_env	*res;
	t_env	*new;
	int		i;

	res = NULL;
	i = 0;
	while (env[i])
	{
		new = ft_str_to_env(env[i]);
		if (!new)
			return (ft_free_env_list(&res), NULL);
		ft_add_new_exp(&res, new);
		i++;
	}
	if (res == NULL)
		res = ft_create_default_exp();
	return (res);
}

void	ft_print_exports_var(t_data *data)
{
	t_env	*cur;

	if (!data)
		return ;
	cur = data->exp_list;
	while (cur)
	{
		ft_putstr_fd("export ", 1);
		if (cur->key)
			ft_putstr_fd(cur->key, 1);
		if (ft_strchr(cur->base, '='))
		{
			ft_putstr_fd("=\"", 1);
			if (cur->value)
				ft_putstr_fd(cur->value, 1);
			ft_putstr_fd("\"\n", 1);
		}
		else
			ft_putstr_fd("\n", 1);
		cur = cur->next;
	}
}

void	ft_remove_exp(t_env **exp_list, char *key)
{
	t_env	*cur;
	t_env	*prev;

	if (!*exp_list)
		return ;
	cur = *exp_list;
	prev = NULL;
	while (cur && ft_strcmp(cur->key, key) != 0)
	{
		prev = cur;
		cur = cur->next;
	}
	if (!cur)
		return ;
	if (prev == NULL)
		*exp_list = cur->next;
	else
		prev->next = cur->next;
	free(cur->key);
	free(cur->value);
	if (cur->base)
		free(cur->base);
	free(cur);
}
