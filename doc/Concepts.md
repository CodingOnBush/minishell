# Minishell important concepts

## Table of contents :

- [Shell Syntax](#Shell-Syntax)
- [Concepts](#Concepts)
	- [Export and Unset](#Export-and-Unset)
	- [Builtins](#Builtins)
	- [Exit status](#Exit-status)
	- [Tokenization](#Tokenization)
- [Specific cases](#Specific-cases)
	- [the ```$``` sign](#the-$-sign----handles-environment-variables)
	- [the ```#``` sign](#the-#-sign)
- [Git training](#Git-training)
- [Sources](#Sources)


## Shell Syntax

First, the Shell is going to read the input (except if it detects a ```#``` command symbol). It will divide it into ```words``` and ```operators``` employing the quoting rules to select which meanings to assign various words and characters. . 

## Concepts:

**Export and Unset** : 

- Local variables can be opened within a shell but if you leave this shell, let's say for a subshell, they won't be defined anymore. The ```export``` command allows us to make the local variable global by adding it to the list of existing global variables (which we get when typing ```env``` in the terminal). If when then try to print this variable in a subshell, it'll be defined and have the value that we set it to.
- The unset command will do the opposite and remove the variable it is given from the list of global variables. It will remove the variable from any shell (including the ine we are in) litteraly unseting its value.

**Builtins** : 

- A command that is implemented internally by the shell itself, rather than by an executable program somewhere in the file system. 

**Exit status** : 

- The value returned by a command to its caller. The value is restricted to eight bits, so the maximum value is 255. 

**Tokenization** : 

- `Tokenization` in the context of a shell refers to the `process of breaking down a command or input into smaller, manageable parts, known as tokens`. These tokens can be as simple as individual words or more complex, including quoted strings and escape sequences. The shell uses tokenization to understand and execute commands by identifying the command itself, its arguments, and any redirection or piping operations.

Here's a simplified explanation of how tokenization works in a shell:

- `Whitespace Separation`: *By default, the shell splits input into tokens based on whitespace characters (spaces, tabs, and newlines). For example, in the command ls -l, ls is one token, -l is another, and they are separated by a space.*

- `*Quoting and Escape Sequences`: *The shell recognizes single quotes (') and double quotes (") to group words together, treating them as a single token even if they contain spaces. For example, echo 'hello world' treats hello world as a single token. Double quotes allow for [escape sequences](https://www.techopedia.com/definition/822/escape-sequence-c) (e.g., echo "hello\tworld"), which are interpreted by the shell.*

- `Special Characters`: *Certain characters have special meanings in the shell and are used to control the flow of commands. These include | (pipe), & (background), ; (command separator), ( and ) (subshell), < and > (input/output redirection). The shell splits tokens at these characters when they are not quoted.*

- ```Complex Tokenization```: *For more complex scenarios, such as handling input like echo 'hello world' | awk '{print $1}', the shell tokenizes the command by recognizing the pipe character | as a separator between two commands, even though there is no whitespace around it.*

In summary, tokenization in a shell is the process of parsing input into tokens that the shell can understand and execute. It involves recognizing whitespace, quotes, escape sequences, and special characters to correctly interpret and execute commands.


**Lexer** : 

- The lexer takes a string of characters as input and produces a sequence of tokens as output. Each token represents a single element of the input string, and the sequence of tokens represents the structure of the input string. The content produced by the lexer is fed to a ```parser```.

*Here's a simplified overview of how lexing might be done in a shell:*


1. `Reading Input`: *The shell reads the command line input, which is a string of characters.*

2. `Tokenizing`: *The lexer goes through the input string character by character. It recognizes tokens based on certain patterns or rules. For example, a word might be defined as a sequence of alphanumeric characters, a redirection operator might be defined as the character '>', and so on.*

3. `Handling Special Characters`: *The lexer also needs to handle special characters like quotes. For example, everything inside double quotes is usually treated as a single token, even if it contains spaces.*

4. `Whitespace and Separators`: *Whitespace characters (spaces and tabs) are often used to separate tokens. Some special characters like semicolons can also act as separators.*

5. `Producing Tokens`: *The lexer produces a sequence of tokens that represent the original command line input. Each token includes information about its type (e.g., word, operator, etc.) and its value (the actual text of the token).*

6. `Passing Tokens to the Parser`: *The tokens are then passed to the parser, which is responsible for interpreting them and executing the corresponding commands.*


## Specific cases :

* **the ```$``` sign --> handles environment variables** : When the ```$``` character is placed between double quotes in Bash, it retains its special meaning and is used for parameter expansion. This means that within double quotes, the $ character is used to reference the value of a variable. For example, if you have a variable var="world", and you use echo "$var", Bash will replace $var with the value of var, which is "world". This behavior is a core part of Bash's string manipulation capabilities and allows for dynamic content to be inserted into strings.

* **the ```#``` sign** :  If the input indicates the beginning of a comment, the shell ignores the comment symbol (‘#’), and the rest of that line. 

## Git training:

I decided to work on my understanding of git commands, so as to avoid mistakes when working collectively on this project. I used the [Learn Git Branching](https://learngitbranching.js.org/) as a support to learn at first.

I then moved on to work with [githug](https://github.com/Gazler/githug) which I found more practical to learn. Indeed it is less graphical but provides on hand experience of git throughtout the problems it offers to solve in the terminal. I used online ressources to find out about the commands that could help me find solutions to the offered problems:
- [Common git commands](http://guides.beanstalkapp.com/version-control/common-git-commands.html)



## Sources:
- [Definition of concepts ](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/bash.html#What-is-Bash_003f)