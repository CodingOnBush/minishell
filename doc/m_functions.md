# Mostafa's functions
Here are some of the functions that we need to understand and use in the project minishell.

## Table of Contents
1. [Signals](#Signals)
2. [tty](#tty)

## Signals
*Functions : signal - sigaction - kill*

Unix signals are a inter-process communication mechanism used in Unix-like operating systems, including Linux.
```
&> man 3 signal

APPLICATION USAGE
	The  sigaction() function provides a more comprehensive and
	reliable mechanism for controlling signals;
	new applications should use sigaction() rather than signal().
```
Thanks to this explanation from the man of signal, we will use **sigaction** instead of **signal** to set a signal handler. And here is the prototype of sigaction :
```c
int sigaction(int signum, const struct sigaction *act, struct sigaction *oldact);
```
- signum : the signal number
- act : a pointer to a struct sigaction that contains the signal handler
- oldact : a pointer to a struct sigaction that will contain the previous signal handler (we will use NULL in most cases)

Let's see an example of how to use sigaction to set a signal handler for SIGINT and SIGUSR1 :
```c
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int	flag = 1;

void	ft_handler(int signum, siginfo_t *info, void *context)
{
	printf("Signal %d detected from pid %d\n", signum, info->si_pid);
	if (signum == SIGUSR1)
		flag = 0;
}

int	main(void)
{
	struct sigaction	act;/*the struct to set a signal handler*/

	act->sa_sigaction = ft_handler;
	act->sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGUSR1, &act, NULL);
	printf("PID: %d\n", getpid());
	while (flag == 1)
		pause();/*a function to wait for a signal*/
	printf("Goodbye\n");
	return (0);
}
```
In this example, we have a main function that will wait for a signal to be sent to the process.\
We use **sigaction** to set a signal handler for SIGINT and SIGUSR1

**sa_sigaction** can take 3 arguments :
- SIG_DFL for the default action
- SIG_IGN to ignore this signal
- A pointer to a signal handling function. (in our case, we use ft_handler)

And because SA_SIGINFO is set in sa_flags we have to use **sa_sigaction** instead of sa_handler.\
In that case we can use the 3rd arguments in ft_handler to get more informations about the signal.

siginfo_t *info	-> contains informations about the signal sent from another process.\
void *context	-> can be used to get informations about the context of the signal.

#### Terminal 1
```bash
$> gcc -o signal signal.c
$> ./signal
PID: 1234
Signal 2 detected from pid 5678
Signal 10 detected from pid 5678
Goodbye
$>
```
#### Terminal 2
```bash
$> kill -2 1234
$> kill -10 1234
$> 
```

In this execution, we can see that the process 1234 is waiting for a signal to be sent.\
We can send a signal to the process using the kill command.\
We can also see that the signal handler is able to get the pid of the process that sent the signal.\
And we can also see that the signal handler is able to get the signal number.

There is a command to send a signal (kill -signal_number pid) but we can also use the C function **kill** to send a signal to a process :
```c
int kill(pid_t pid, int sig); // returns 0 on success, -1 on error
```

## tty (teletypewriter)
*Functions : isatty, ttyname, ttyslot*

**What is tty ?**\
A teletypewriter (TTY) is a communication device that allows users to interact with computers and other telecommunication systems. In this context, the term 'device' typically refers to the terminal used for TTY communication. Other examples of devices commonly used in computing and telecommunications include printers, mice, keyboards, etc.

**How to use these functions ?**\
isatty &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ➜ &nbsp;&nbsp;&nbsp; want to know if a file descriptor is associated with a terminal.\
ttyname &nbsp; ➜ &nbsp;&nbsp;&nbsp; To get the name of a terminal associated with a file descriptor.\
ttyslot &nbsp;&nbsp;&nbsp;&nbsp;&nbsp; ➜ &nbsp;&nbsp;&nbsp; To get number of a terminal associated with the standard input.

**Prototypes**
```c
int isatty(int fd);
/*It returns 1 if the file descriptor is associated with a terminal, 0 if it is not, -1 on error.*/

char *ttyname(int fd);
/*It returns the name of the terminal associated with the file descriptor, NULL on error.*/

int ttyslot(void);
/*It returns the number of the terminal associated with the standard input, -1 on error.*/
```

**Example**
```c
#include <stdio.h>
#include <unistd.h>

int	main(void)
{
	printf("isatty(0): %d\n", isatty(0));
	printf("isatty(1): %d\n", isatty(1));
	printf("isatty(2): %d\n", isatty(2));
	printf("ttyname(0): %s\n", ttyname(0));
	printf("ttyname(1): %s\n", ttyname(1));
	printf("ttyname(2): %s\n", ttyname(2));
	printf("ttyslot(): %d\n", ttyslot());
	return (0);
}
```

#### Execution
```bash
$> gcc -o tty tty.c
$> ./tty
isatty(0): 1
isatty(1): 1
isatty(2): 1
ttyname(0): /dev/ttys000
ttyname(1): /dev/ttys000
ttyname(2): /dev/ttys000
ttyslot(): 0
$>
```

In this example, we can see that the standard input, output and error are associated with a terminal.\
We can also see that the name of the terminal associated with the standard input, output and error is /dev/ttys000.\
And we can also see that the number of the terminal associated with the standard input is 0.

## input, output and error

The **standard input** is a file descriptor that is associated with the terminal :
- When we use the scanf function, it reads from the standard input
- When we use the cat command without arguments, it reads from the standard input.

The **standard output** is a file descriptor that is associated with the terminal :
- When we use the printf function, it writes to the standard output.
- When we use the ls command without arguments, it writes to the standard output.

The **standard error** is a file descriptor that is associated with the terminal :
- When we use the perror function, it writes to the standard error.
- When we use the write function with the file descriptor 2, it writes to the standard error.
- When we use the ls command with a non-existing directory, it writes to the standard error.

**Redirection** :
- We can use the < and > operators to redirect the standard input and output.\
- We can use the 2> operator to redirect the standard error.\
- We can use the | operator to pipe the standard output to the standard input of another command.