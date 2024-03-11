# Mostafa's functions
Here are some of the functions that we need to understand and use in the project minishell.

## Table of Contents
1. [signals](#signals)
2. [tty](#tty)
3. [getenv](#getenv)
4. [ioctl](#ioctl)
5. [get file status](#get-file-status)
6. [directory manipulation](#directory-manipulation)
7. [terminal handling](#terminal-handling)

## signals
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

### input, output and error

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

## getenv
*Function : getenv*

**What is getenv ?**\
The getenv function searches the environment list to find the environment variable name, and returns a pointer to the corresponding value string.

**How to use it ?**\
```c
char *getenv(const char *name);
```
- name : the name of the environment variable
- returns a pointer to the value of the environment variable, NULL if the environment variable does not exist.

**Example**
```c
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	printf("HOME: %s\n", getenv("HOME"));
	printf("PATH: %s\n", getenv("PATH"));
	printf("PWD: %s\n", getenv("PWD"));
	printf("USER: %s\n", getenv("USER"));
	printf("SHELL: %s\n", getenv("SHELL"));
	return (0);
}
```
## ioctl
*Function : ioctl*

**What is ioctl ?**\
The ioctl function manipulates the underlying device parameters of special files. For example, we can use it to get the size of the terminal.

**What are the underlying device parameters of special files ?**\
It is the parameters of the device that is associated with the file descriptor.\
For example, the terminal is a device that is associated with the file descriptor 0, 1 and 2.\
And we can use ioctl to get the size of the terminal or to set the size of the terminal.

**Is it only for the terminal ?**\
No, we can use ioctl to manipulate the underlying device parameters of any special file.\
For example, we can use it to get the size of a window, to set the baud rate of a serial port, to set the IP address of a network interface, etc.

**How to use it ?**
```c
int ioctl(int d, unsigned long request, ...);
```
- d : the file descriptor of the device
- request : the request code
- ... : the arguments of the request

**Example**
```c
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

int	main(void)
{
	struct winsize	ws;

	ioctl(0, TIOCGWINSZ, &ws);
	printf("rows: %d\n", ws.ws_row);
	printf("columns: %d\n", ws.ws_col);
	return (0);
}
```

## get file status
*Function : stat, lstat and fstat*

**What is stat ?**\
The stat function returns information about a file, in the buffer pointed to by the buf argument. No permissions are required on the file itself, but-in the case of stat()-execute (search) permission is required on all of the directories in pathname that lead to the file.

**What is lstat ?**\
The lstat function is identical to stat(), except that if pathname is a symbolic link, then it returns information about the link itself, not the file that it refers to.

**What is fstat ?**\
The fstat function is identical to stat(), except that the file about which information is to be retrieved is specified by the file descriptor fd.

**How to use it ?**
```c
int stat(const char *pathname, struct stat *buf);
int lstat(const char *pathname, struct stat *buf);
int fstat(int fd, struct stat *buf);
```
- pathname : the path of the file
- fd : the file descriptor of the file
- buf : a pointer to a struct stat that will contain the information about the file
- returns 0 on success, -1 on error

**this is the structure stat**
```c
struct stat {
	dev_t     st_dev;         /* ID of device containing file */
	ino_t     st_ino;         /* inode number */
	mode_t    st_mode;        /* protection */
	nlink_t   st_nlink;       /* number of hard links */
	uid_t     st_uid;         /* user ID of owner */
	gid_t     st_gid;         /* group ID of owner */
	dev_t     st_rdev;        /* device ID (if special file) */
	off_t     st_size;        /* total size, in bytes */
	blksize_t st_blksize;     /* blocksize for file system I/O */
	blkcnt_t  st_blocks;      /* number of 512B blocks allocated */
	time_t    st_atime;       /* time of last access */
	time_t    st_mtime;       /* time of last modification */
	time_t    st_ctime;       /* time of last status change */
};
```

**An example with stat :**
```c
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int	main(void)
{
	struct stat	buf;

	stat("file", &buf);
	printf("st_dev: %d\n", buf.st_dev);
	printf("st_ino: %d\n", buf.st_ino);
	printf("st_mode: %d\n", buf.st_mode);
	printf("st_nlink: %d\n", buf.st_nlink);
	printf("st_uid: %d\n", buf.st_uid);
	printf("st_gid: %d\n", buf.st_gid);
	printf("st_rdev: %d\n", buf.st_rdev);
	printf("st_size: %d\n", buf.st_size);
	printf("st_blksize: %d\n", buf.st_blksize);
	printf("st_blocks: %d\n", buf.st_blocks);
	printf("st_atime: %d\n", buf.st_atime);
	printf("st_mtime: %d\n", buf.st_mtime);
	printf("st_ctime: %d\n", buf.st_ctime);
	return (0);
}
```
**An example with fstat :**
```c
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int	main(void)
{
	int		fd;
	struct stat	buf;

	fd = open("file", O_RDONLY);
	fstat(fd, &buf);
	printf("st_dev: %d\n", buf.st_dev);
	printf("st_ino: %d\n", buf.st_ino);
	printf("st_mode: %d\n", buf.st_mode);
	printf("st_nlink: %d\n", buf.st_nlink);
	printf("st_uid: %d\n", buf.st_uid);
	printf("st_gid: %d\n", buf.st_gid);
	printf("st_rdev: %d\n", buf.st_rdev);
	printf("st_size: %d\n", buf.st_size);
	printf("st_blksize: %d\n", buf.st_blksize);
	printf("st_blocks: %d\n", buf.st_blocks);
	printf("st_atime: %d\n", buf.st_atime);
	printf("st_mtime: %d\n", buf.st_mtime);
	printf("st_ctime: %d\n", buf.st_ctime);
	close(fd);
	return (0);
}
```
**An example with lstat :**
```c
#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

int	main(void)
{
	struct stat	buf;

	lstat("file", &buf);
	printf("st_dev: %d\n", buf.st_dev);
	printf("st_ino: %d\n", buf.st_ino);
	printf("st_mode: %d\n", buf.st_mode);
	printf("st_nlink: %d\n", buf.st_nlink);
	printf("st_uid: %d\n", buf.st_uid);
	printf("st_gid: %d\n", buf.st_gid);
	printf("st_rdev: %d\n", buf.st_rdev);
	printf("st_size: %d\n", buf.st_size);
	printf("st_blksize: %d\n", buf.st_blksize);
	printf("st_blocks: %d\n", buf.st_blocks);
	printf("st_atime: %d\n", buf.st_atime);
	printf("st_mtime: %d\n", buf.st_mtime);
	printf("st_ctime: %d\n", buf.st_ctime);
	return (0);
}
```

## directory manipulation
*Functions : opendir, readdir, closedir*

**What is opendir ?**\
The opendir function opens a directory stream corresponding to the directory name, and returns a pointer to the directory stream. The stream is positioned at the first entry in the directory and the next call to readdir will read the first entry in the directory.

**What is readdir ?**\
The readdir function returns a pointer to a dirent structure representing the next directory entry in the directory stream pointed to by dirp. It returns NULL on reaching the end of the directory or on error.

**What is closedir ?**\
The closedir function closes the directory stream associated with dirp. A successful call to closedir also closes the underlying file descriptor associated with dirp.

**How to use it ?**
```c
DIR *opendir(const char *name);
struct dirent *readdir(DIR *dirp);
int closedir(DIR *dirp);
```
- name : the name of the directory
- dirp : a pointer to a DIR structure that represents the directory stream
- returns a pointer to the directory stream, NULL on error

**this is the structure dirent**
```c
struct dirent {
	ino_t          d_ino;       /* inode number */
	off_t          d_off;       /* offset to the next dirent */
	unsigned short d_reclen;    /* length of this record */
	unsigned char  d_type;      /* type of file; not supported by all file system types */
	char           d_name[256]; /* filename */
};
```

**Example**
```c
#include <stdio.h>
#include <dirent.h>

int	main(void)
{
	DIR				*dir;
	struct dirent	*entry;

	dir = opendir(".");
	while ((entry = readdir(dir)) != NULL)
		printf("%s\n", entry->d_name);
	closedir(dir);
	return (0);
}
```
## Terminal handling
*Functions : tcsetattr, tcgetattr, tgetent, tgetflag, tgetnum, tgetstr, tgoto, tputs*

A terminal has attributes to define and control different aspects of its operation. These attributes allow you to configure behaviors such as input mode, output mode, signal control, etc.\
Theses functions are used to manipulate the terminal attributes.

**What is tcgetattr ?**
```c
int tcgetattr(int fd, struct termios *termios_p);
```
The tcgetattr function gets the parameters associated with the terminal referred to by fd and stores them in the termios structure referenced by termios_p.

**What is the termios structure ?**\
The termios structure is a data structure that contains the terminal attributes.\
It is defined in the termios.h header file and it contains the following members :
```c
struct termios {
	tcflag_t c_iflag;	/* input modes */
	tcflag_t c_oflag;	/* output modes */
	tcflag_t c_cflag;	/* control modes */
	tcflag_t c_lflag;	/* local modes */
	cc_t c_cc[NCCS];	/* control characters */
	speed_t c_ispeed;	/* input speed */
	speed_t c_ospeed;	/* output speed */
};
```

**What is tcsetattr ?**
```c
int tcsetattr(int fd, int optional_actions, const struct termios *termios_p);
```
The tcsetattr function sets the parameters associated with the terminal referred to by fd from the termios structure referenced by termios_p.

**What is tgetent ?**\
```c
int tgetent(char *bp, const char *name);
```
The tgetent function loads the termcap database and returns the number of bytes in the buffer area. The buffer area is used by the other tget functions to store the data that they retrieve from the termcap database.

**Why do we have a termcap database ?**\
The termcap database is a library of capabilities that are used to control the terminal.\
For example, it contains the capabilities to move the cursor, to clear the screen, to change the color, etc.\
And then we can use these functions :
```c
int tgetflag(const char *id);
int tgetnum(const char *id);
char *tgetstr(const char *id, char **area);
char *tgoto(const char *cap, int col, int row);
int tputs(const char *str, int affcnt, int (*putc)(int));
```

**What is tgetflag ?**\
The tgetflag function gets the boolean value of the capability name (id) from the termcap database.

**What is tgetnum ?**\
The tgetnum function gets the numeric value of the capability name (id) from the termcap database.

**What is tgetstr ?**\
The tgetstr function gets the string value of the capability name (id) from the termcap database and the area is a buffer.

**What is tgoto ?**\
The tgoto function returns a string that is the result of expanding the string cap with the parameters given by the varargs list.

**What is tputs ?**\
The tputs function writes the string cp to the terminal.

**Example**
```c
#include <stdio.h>
#include <termios.h>
#include <curses.h>
#include <term.h>

int	main(void)
{
	struct termios	term;
	char			*bp;
	int				ret;

	tcgetattr(0, &term);// get the current attributes
	term.c_lflag &= ~(ICANON);// disable canonical mode
	term.c_lflag &= ~(ECHO);// disable echo
	tcsetattr(0, 0, &term);// set the new attributes
	bp = (char *)malloc(2048);
	if (!bp)
		return (1);
	ret = tgetent(bp, getenv("TERM"));// load the termcap database
	printf("ret: %d\n", ret);
	printf("tgetflag: %d\n", tgetflag("am"));// auto margins
	printf("tgetnum: %d\n", tgetnum("co"));// number of columns
	printf("tgetstr: %s\n", tgetstr("cl", &bp));// clear the screen
	printf("tgoto: %s\n", tgoto("cm", 1, 1));// move the cursor to the position (1, 1)
	tputs(tgetstr("cl", &bp), 1, putchar);// clear the screen using tputs and putchar as putc function
	tcsetattr(0, 0, &term);// restore the old attributes
	return (0);
}
```