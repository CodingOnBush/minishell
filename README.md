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
    - and an ```int clear_undo``` which if non-zero, clears the undo list associated with the current line. The undo list associated with the current line in           the GNU Readline library is essentially a history of changes made to the text of the line. When you modify the text in the line, Readline can keep track           of these modifications, allowing you to undo them one by one. This feature is particularly useful for correcting mistakes or changing your mind about a            line of input without having to start over from scratch.

The undo list can be modified or cleared using various Readline functions.


Specific cases :

* **the ```$``` sign --> handles environment variables** : When the $ character is placed between double quotes in Bash, it retains its special meaning and is used for parameter expansion. This means that within double quotes, the $ character is used to reference the value of a variable. For example, if you have a variable var="world", and you use echo "$var", Bash will replace $var with the value of var, which is "world". This behavior is a core part of Bash's string manipulation capabilities and allows for dynamic content to be inserted into strings.


## Git training:

I decided to work on my understanding of git commands, so as to avoid mistakes when working collectively on this project. I used the [Learn Git Branching](https://learngitbranching.js.org/) as a support to learn at first.

I then moved on to work with [githug](https://github.com/Gazler/githug) which I found more practical to learn. Indeed it is less graphical but provides on hand experience of git throughtout the problems it offers to solve in the terminal. I used online ressources to find out about the commands that could help me find solutions to the offered problems:
- [Common git commands](http://guides.beanstalkapp.com/version-control/common-git-commands.html)
