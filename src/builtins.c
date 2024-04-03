/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/27 22:46:05 by momrane           #+#    #+#             */
/*   Updated: 2024/04/03 22:59:43 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

static void	ft_print_env(char **env)
{
	int	i;

	i = 0;
	if (!env)
		return ;
	while (env[i] != NULL)
	{
		printf("%s\n", env[i]);
		i++;
	}
}

int	ft_pwd(t_arg *arg_list)
{
	char	*cwd;

	cwd = ft_getcwd();
	if (cwd == NULL)
	{
		perror(arg_list->value);
		return (FAIL);
	}
	printf("%s\n", cwd);
	free(cwd);
	return (SUCCESS);
}

int	ft_exec_builtin(t_data *data, t_cmd *cmd)
{
	int	len;

	len = ft_strlen(cmd->arg_list->value);
	if (ft_strncmp(cmd->arg_list->value, "pwd", len) == 0)
		return (ft_pwd(cmd->arg_list->next));
	if (ft_strncmp(cmd->arg_list->value, "cd", len) == 0)
		return (ft_change_dir(cmd));
	if (ft_strncmp(cmd->arg_list->value, "echo", len) == 0)
		return (ft_echo(cmd));
	if (ft_strncmp(cmd->arg_list->value, "env", len) == 0)
	{
		ft_print_env(data->env);
		return (SUCCESS);
	}
	return (SUCCESS);
}

char	*ft_getcwd(void)
{
	char	*cwd;

	cwd = malloc(1024 * sizeof(char));
	if (!cwd)
		return (NULL);
	getcwd(cwd, 1024);
	return (cwd);
}

int	ft_change_dir(t_cmd *cmd)
{
	char	*path;

	if (!cmd || !cmd->arg_list || !cmd->arg_list->next)
		return (FAIL);
	path = cmd->arg_list->next->value;
	// check if path match with our conditions
	if (chdir(path) == -1)
	{
		perror(path);
		return (FAIL);
	}
	return (SUCCESS);
}

static t_arg	*ft_find_n_option(t_arg *arg_list)
{
	t_arg	*cur;
	t_arg	*last;
	char	*str;

	cur = arg_list->next;
	last = NULL;
	while (cur)
	{
		str = cur->value;
		if (!str || !str[0] || str[0] != '-')
			return (last);
		str++;
		while (str && *str != '\0' && *str == 'n')
			str++;
		if (*str == '\0')
			last = cur;
		else
			return (last);
		cur = cur->next;
	}
	return (NULL);
}

int	ft_echo(t_cmd *cmd)
{
	t_arg	*cur;
	int		add_newline;
	char	*str;
	t_arg	*option;
	
	add_newline = YES;
	option = ft_find_n_option(cmd->arg_list);
	if (option != NULL)
	{
		add_newline = NO;
		cur = option->next;
	}
	else
		cur = cmd->arg_list->next;
	while (cur != NULL)
	{
		str = cur->value;
		printf("%s", str);
		if (cur->next != NULL)
			printf(" ");
		cur = cur->next;
	}
	if (add_newline == YES)
		printf("\n");
	return (SUCCESS);
}
