# Minishell

## Research:

### Functions:

* ```Readline()``` is going to read a line in the terminal and return it malloced (meaning that we will have to fre it ourselves). If a prompt is given as an argument, it is displayed in the terminal. Example :

  ```c
                #include <stdio.h>
                #include <readline/readline.h>
                #include <readline/history.h>
            
                int main(void)
                {
                    char *rl;
                    rl = readline("Prompt > ");
                    printf("%s\n", rl);
                    return (0);
                }
  ```

Compiling and running this program (with ```cc minishell.c -o minishell -lreadline```) will give the following output:

  ```
        $> ./minishell
        Prompt > Hi ! How are you ?
        Hi ! How are you ?
        $>
  ```

* ```rl_clear_history()``` is used to clear the history list of previously entered lines. The following input shows how to use readline to read input, add it to the history and then clear the history.

    ```c
                #include <stdio.h>
                #include <stdlib.h>
                #include <readline/readline.h>
                #include <readline/history.h>
                
                int main() {
                    // Readline setup
                    using_history(); // Enable history
                
                    // Read and add to history
                    char *input1 = readline("Enter command 1: ");
                    add_history(input1);
                
                    char *input2 = readline("Enter command 2: ");
                    add_history(input2);
                
                    // Display entered commands
                    printf("You entered:\n1. %s\n2. %s\n", input1, input2);
                
                    // Clear history
                    rl_clear_history();
                
                    // Free allocated memory
                    free(input1);
                    free(input2);
                
                    return 0;
                }
    ```

If I want to see the direct effect of rl_clear_history() I can print the history, to which input1 and input2 were added. Here is how :

  ```c
                #include <stdio.h>
                #include <stdlib.h>
                #include <readline/readline.h>
                #include <readline/history.h>
                
                int main() {
                    // Readline setup
                    using_history(); // Enable history
                
                    // Read and add to history
                    char *input1 = readline("Enter command 1: ");
                    add_history(input1);
                
                    char *input2 = readline("Enter command 2: ");
                    add_history(input2);
                
                    // Display entered commands
                    printf("You entered:\n1. %s\n2. %s\n", input1, input2);
                
                    // Print history
                    HIST_ENTRY **history_list = history_list();
                    if (history_list != NULL) {
                        printf("Command history:\n");
                        for (int i = 0; history_list[i] != NULL; ++i) {
                            printf("%d. %s\n", i + 1, history_list[i]->line);
                        }
                    }
                
                    // Free allocated memory
                    free(input1);
                    free(input2);
                
                    return 0;
                }
  ```

- ```rl_on_new_line()``` does not take any argument and does not return a value. It only resets Readline's inernal state to reflect that a new line has been started for the next readline operations (printing the promp, eading the input etc.) to work correctly.

    ```c
                #include <stdio.h>
                #include <readline/readline.h>
                #include <readline/history.h>
                
                int main() {
                    char *line;
                
                    /* Initialize Readline */
                    rl_readline_name = "my-readline-app";
                    rl_prompt = "my-prompt> ";
                
                    while ((line = readline(rl_prompt)) != NULL) {
                        /* Process the line */
                        printf("You entered: %s\n", line);
                
                        /* Add the line to the history. */
                        add_history(line);
                
                        /* Manually output a newline character */
                        putchar('\n');
                
                        /* Inform Readline that a new line has started */
                        rl_on_new_line();
                
                        /* Clean up */
                        free(line);
                    }
                
                    return 0;
                }
    ```

- ```rl_replace_line``` canbe useful in custom readline functions or when you need to modify the line that the user is currently editing. It takes 2 arguments :

    - a ```const char *text``` which is the new content for the line
    - and an ```int clear_undo``` which if non-zero, clears the undo list associated with the current line. The undo list associated with the current line in           the GNU Readline library is essentially a history of changes made to the text of the line. When you modify the text in the line, Readline can keep track           of these modifications, allowing you to undo them one by one. This feature is particularly useful for correcting mistakes or changing your mind about a            line of input without having to start over from scratch. The undo list can be modified or cleared using various Readline functions.

  Here is an example of how the function can be used :

```c
    #include <readline/readline.h>
    #include <readline/history.h>
    
    /* Custom Readline function that replaces the current line with "Hello, World!" */
    void my_custom_function (int count, int key) {
        rl_replace_line("Hello, World!", 1);
        rl_end_undo_group();
    }
    
    int main() {
    /* Bind the custom function to a key, e.g., Ctrl-x */
      rl_bind_key('\030', my_custom_function);
    
    /* Start Readline */
      char *line = readline("Enter a command: ");
      if (line) 
      {
        printf("You entered: %s\n", line);
        free(line);
      }
        return 0;
    }
```

- ```rl_redisplay()``` is designed to refresh the display on the screen to reflect the current content of ```rl_line_buffer```. This function is crucial for ensuring that the user's view of the command line input matches the actual state of the input buffer. It forces the line to be updated and redisplayed, regardless of whether Readline thinks the screen display is correct. ```rl_redisplay``` does not take any arguments. An example of how rl_redisplay works:

- ```add_history()``` adds a line to history list maintained by readline. The line is added to the end of the list. If the history list is full, the first element is removed. The line is added to the history list without any modification. The history list is a circular list, so when the end is reached, the next element is the first one. The history list is not saved to disk until the application exits. When ```add_history()``` is called, it adds the provided line to the history list, making it available for later recall. The function returns 0 on success and -1 on error. Here is an example of how to use add_history:

```c
    #include <stdio.h>
    #include <readline/readline.h>
    #include <readline/history.h>
    
    int main() {
        // Readline setup
        using_history(); // Enable history
    
        // Read and add to history
        char *input1 = readline("Enter command 1: ");
        add_history(input1);
    
        char *input2 = readline("Enter command 2: ");
        add_history(input2);
    
        // Display entered commands
        printf("You entered:\n1. %s\n2. %s\n", input1, input2);
    
        // Free allocated memory
        free(input1);
        free(input2);
    
        return 0;
    }
```

- ```wait3()```: This system call is similar to wait(), but it additionally returns resource usage information about the terminated child process. The resource usage information is stored in a struct rusage that is passed as an argument to wait3(). This allows the parent process to get detailed information about the resources used by the child process, such as CPU time, memory usage, and more. However, wait3() is considered legacy and is not part of the POSIX standard. It is implemented on top of the wait4() system call in Linux 5.

- ```wait4()```: This system call is similar to wait3(), but it allows the parent process to specify a particular child process to wait for by using its process ID (PID). This makes wait4() more flexible than wait3() and wait(), as it can be used to wait for a specific child process or any child process, depending on the PID argument. Like wait3(), wait4() also returns resource usage information about the terminated child process in a struct rusage. The wait4() system call is part of the BSD style of system calls and is not standardized across all Unix-like operating systems

- ```dup()``` : The ```dup()``` function is used to duplicate an existing file descriptor, returning a new file descriptor that points to the same open file description as the original. The new file descriptor is guaranteed to have the lowest integer value available among the unused file descriptors. This feature is crucial for I/O redirection, as it allows processes to redirect their standard input, output, or error streams to different files or devices without affecting the original file descriptor.

Here's a basic example of how ```dup()``` can be used for redirection:
```c
#include <fcntl.h>
#include <unistd.h>

int main() {
    int fd_redirect_to = open("file", O_CREAT);
    close(1); // Close stdout
    int fd_to_redirect = dup(fd_redirect_to); // Duplicate fd_redirect_to, now stdout
    close(fd_redirect_to); // Close the original file descriptor
    // Now, anything written to stdout (file descriptor 1) goes into "file"
    return 0;
}
```
On the other hand, ```dup2()``` is similar to ```dup()``` but allows specifying the new file descriptor number. If the specified new file descriptor is already open, it is silently closed before being reused. This makes ```dup2()``` more flexible than ```dup()``` for certain redirection tasks, especially when you need to redirect to a specific file descriptor number.

- ```strerror()``` : The ```strerror()``` function in C is used to map an error number to a human-readable error message string. It takes an integer error number as an argument and returns a pointer to a string that describes the error. This function is part of the C standard library and is defined in the ```<string.h>``` header file. The error strings produced by strerror() depend on the developing platform and compiler. 

```c
#include <stdio.h>
#include <string.h>
#include <errno.h>

int main() {
    FILE *fp;

    fp = fopen("file.txt", "r");
    if (fp == NULL) {
        printf("Error: %s\n", strerror(errno));
    }

    return 0;
}
```

## Specific cases :

* **the ```$``` sign --> handles environment variables** : When the ```$``` character is placed between double quotes in Bash, it retains its special meaning and is used for parameter expansion. This means that within double quotes, the $ character is used to reference the value of a variable. For example, if you have a variable var="world", and you use echo "$var", Bash will replace $var with the value of var, which is "world". This behavior is a core part of Bash's string manipulation capabilities and allows for dynamic content to be inserted into strings.


## Git training:

I decided to work on my understanding of git commands, so as to avoid mistakes when working collectively on this project. I used the [Learn Git Branching](https://learngitbranching.js.org/) as a support to learn at first.

I then moved on to work with [githug](https://github.com/Gazler/githug) which I found more practical to learn. Indeed it is less graphical but provides on hand experience of git throughtout the problems it offers to solve in the terminal. I used online ressources to find out about the commands that could help me find solutions to the offered problems:
- [Common git commands](http://guides.beanstalkapp.com/version-control/common-git-commands.html)

## Concepts:

**Export and Unset** : local variables can be opened within a shell but if you leave this shell, let's say for a subshell, they won't be defined anymore. The ```export``` command allows us to make the local variable global by adding it to the list of existing global variables (which we get when typing ```env``` in the terminal). If when then try to print this variable in a subshell, it'll be defined and have the value that we set it to.
The unset command will do the opposite and remove the variable it is given from the list of global variables. It will remove the variable from any shell (including the ine we are in) litteraly unseting its value.