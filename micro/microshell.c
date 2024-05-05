/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   microshell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 13:09:30 by momrane           #+#    #+#             */
/*   Updated: 2024/05/05 14:02:11 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

#define ERR 1
#define OK 0

#define WD 0
#define RD 1

#define WRITE_END 0
#define READ_END 1

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define FATAL "error: fatal\n"

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_err(char *msg)
{
	write(STDERR, msg, ft_strlen(msg));
	return (ERR);
}

int	ft_cd(char **av, int i)
{
	if (i != 2)
		return (ft_err("error: cd: bad arguments\n"));
	if (chdir(av[1]) == -1)
	{
		ft_err("error: cd: cannot change directory to ");
		ft_err(av[1]);
		ft_err("\n");
		return (ERR);
	}
	return (OK);
}

int	ft_exec(char **av, int i, char **env)
{
	int	fd[2];
	int	in_pipe;
	int	pid;
	int	status;

	in_pipe = 0;
	if (av[i] != NULL && strcmp(av[i], "|") == 0)
		in_pipe = 1;
	if (!in_pipe && strcmp(av[0], "cd") == 0)
		return (ft_cd(av, i));
	if (in_pipe == 1)
		pipe(fd);
	pid = fork();
	if (pid == -1)
		return (ERR);
	if (pid == 0)
	{
		av[i] = NULL;
		if (in_pipe == 1)
		{
			dup2(fd[READ_END], STDOUT);
			close(fd[READ_END]);
			close(fd[WRITE_END]);
		}
		if (strcmp(av[0], "cd") == 0)
			return (ft_cd(av, i));
		execve(av[0], av, env);
		return (ERR);
	}
	waitpid(pid, &status, 0);
	if (in_pipe == 1)
	{
		dup2(fd[WRITE_END], STDIN);
		close(fd[READ_END]);
		close(fd[WRITE_END]);
	}
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

int	main(int ac, char **av, char **env)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (ac <= 1)
		return (OK);
	while (av[i] && av[i + 1])
	{
		av += i + 1;
		i = 0;
		while (av[i] && strcmp(av[i], "|") != 0 && strcmp(av[i], ";") != 0)
			i++;
		if (i != 0)
			status = ft_exec(av, i, env);
	}
	return (status);
}
