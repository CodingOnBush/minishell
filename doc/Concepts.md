# Minishell important concepts

## Concepts:

**Export and Unset** : 

- Local variables can be opened within a shell but if you leave this shell, let's say for a subshell, they won't be defined anymore. The ```export``` command allows us to make the local variable global by adding it to the list of existing global variables (which we get when typing ```env``` in the terminal). If when then try to print this variable in a subshell, it'll be defined and have the value that we set it to.
- The unset command will do the opposite and remove the variable it is given from the list of global variables. It will remove the variable from any shell (including the ine we are in) litteraly unseting its value.

**Builtins** : 

- A command that is implemented internally by the shell itself, rather than by an executable program somewhere in the file system. 

**Exit status** : 

- The value returned by a command to its caller. The value is restricted to eight bits, so the maximum value is 255. 

## Specific cases :

* **the ```$``` sign --> handles environment variables** : When the ```$``` character is placed between double quotes in Bash, it retains its special meaning and is used for parameter expansion. This means that within double quotes, the $ character is used to reference the value of a variable. For example, if you have a variable var="world", and you use echo "$var", Bash will replace $var with the value of var, which is "world". This behavior is a core part of Bash's string manipulation capabilities and allows for dynamic content to be inserted into strings.


## Git training:

I decided to work on my understanding of git commands, so as to avoid mistakes when working collectively on this project. I used the [Learn Git Branching](https://learngitbranching.js.org/) as a support to learn at first.

I then moved on to work with [githug](https://github.com/Gazler/githug) which I found more practical to learn. Indeed it is less graphical but provides on hand experience of git throughtout the problems it offers to solve in the terminal. I used online ressources to find out about the commands that could help me find solutions to the offered problems:
- [Common git commands](http://guides.beanstalkapp.com/version-control/common-git-commands.html)



## Sources:
- [Definition of concepts ](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#What-is-Bash_003f)