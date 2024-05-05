/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:41:27 by momrane           #+#    #+#             */
/*   Updated: 2024/05/04 13:36:38 by momrane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*

Source:
https://github.com/pasqualerossi/42-School-Exam-Rank-04/blob/main/microshell.c

Instructions:
./sub.txt

*/

#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

#define STDIN 0
#define STDOUT 1
#define STDERR 2

#define ERR 1
#define OK 0

#define SYSERR "error: fatal\n"

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

void	ft_putstr_fd(char *str, int fd)
{
	write(fd, str, ft_strlen(str));
}

int	ft_err(char *str)
{
	ft_putstr_fd(str, STDERR);
	return (ERR);
}

int	cd(char **argv, int i)
{
	if (i != 2)
		return (ft_err("error: cd: bad arguments\n"));
	if (chdir(argv[1]) == -1)
	{
		ft_err("error: cd: cannot change directory to ");
		ft_err(argv[1]);
		ft_err("\n");
		return (ERR);
	}
	return (0);
}

int	exec(char **argv, int i, char **env)
{
	int	fd[2];
	int	status;
	int	has_pipe;
	int	pid;

	has_pipe = 0;
	if (argv[i] != NULL && strcmp(argv[i], "|") == 0)
		has_pipe = 1;

	if (!has_pipe && !strcmp(*argv, "cd"))
		return (cd(argv, i));
	
	if (has_pipe && pipe(fd) == -1)
		return (ft_err(SYSERR));
	
	pid = fork();
	if (pid == -1)
		return (ft_err(SYSERR));
	if (pid == 0)
	{
		argv[i] = 0;
		if (has_pipe && (dup2(fd[1], STDOUT_FILENO) == -1 || close(fd[STDIN_FILENO]) == -1 || close(fd[STDOUT_FILENO]) == -1))
			return (ft_err(SYSERR));
		if (!strcmp(*argv, "cd"))
			return (cd(argv, i));
		execve(*argv, argv, env);
		return (ft_err("error: cannot execute "), ft_err(*argv), ft_err("\n"));
	}
	waitpid(pid, &status, 0);
	if (has_pipe && (dup2(fd[0], STDIN_FILENO) == -1 || close(fd[STDIN_FILENO]) == -1 || close(fd[STDOUT_FILENO]) == -1))
		return (ft_err(SYSERR));
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

int	main(int argc, char **argv, char **env)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (argc <= 1)
		return (0);
	while (argv[i] && argv[i + 1])
	{
		// i++;
		argv += i + 1;
		i = 0;
		ft_putstr_fd("current command : ", 1);
		ft_putstr_fd(*argv, 1);
		ft_putstr_fd("\n", 1);
		while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
			i++;
		if (i != 0)
			status = exec(argv, i, env);
	}
	return (status);
}
