/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   micro.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momrane <momrane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 19:41:27 by momrane           #+#    #+#             */
/*   Updated: 2024/05/03 19:53:35 by momrane          ###   ########.fr       */
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

int	err(char *str)
{
	while (*str)
		write(2, str++, 1);
	return (1);
}

int	cd(char **argv, int i)
{
	if (i != 2)
		return (err("error: cd: bad arguments\n"));
	if (chdir(argv[1]) == -1)
		return (err("error: cd: cannot change directory to "), err(argv[1]),
			err("\n"));
	return (0);
}

int	exec(char **argv, int i)
{
	int	fd[2];
	int	status;
	int	has_pipe;
	int	pid;

	has_pipe = argv[i] && !strcmp(argv[i], "|");
	printf("has_pipe: %d\n", has_pipe);
	if (!has_pipe && !strcmp(*argv, "cd"))
		return (cd(argv, i));
	if (has_pipe && pipe(fd) == -1)
		return (err("error: fatal\n"));
	pid = fork();
	if (pid == -1)
		return (err("error: fatal\n"));
	if (pid == 0)
	{
		argv[i] = 0;
		if (has_pipe && (dup2(fd[1], STDOUT_FILENO) == -1 || close(fd[STDIN_FILENO]) == -1
				|| close(fd[STDOUT_FILENO]) == -1))
			return (err("error: fatal\n"));
		if (!strcmp(*argv, "cd"))
			return (cd(argv, i));
		execve(*argv, argv, __environ);
		return (err("error: cannot execute "), err(*argv), err("\n"));
	}
	waitpid(pid, &status, 0);
	if (has_pipe && (dup2(fd[0], STDIN_FILENO) == -1 || close(fd[STDIN_FILENO]) == -1
			|| close(fd[STDOUT_FILENO]) == -1))
		return (err("error: fatal\n"));
	return (WIFEXITED(status) && WEXITSTATUS(status));
}

int	main(int argc, char **argv)
{
	int	i;
	int	status;

	i = 0;
	status = 0;
	if (argc <= 1)
		return (0);
	while (argv[i] && argv[++i])
	{
		argv += i;
		i = 0;
		while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
			i++;
		if (i != 0)
			status = exec(argv, i);
	}
	return (status);
}
