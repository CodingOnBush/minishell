# Minishell – A Simplified Unix Shell in C (42 Project)

## Introduction  
**Minishell** is a simplified reproduction of a **Unix shell**, inspired by the well-known Bash shell. Developed in C, this program allows users to interact with the operating system through a command-line interface. Users can type textual commands (e.g., `ls` to list files) and receive system feedback, just like in a traditional terminal. The goal of Minishell is to provide the core functionalities of a shell in an educational and streamlined environment, while remaining user-friendly.

## Project Context  
This project was developed **in pairs** as part of the training at **42 School**. It was our **first major system programming project**, immersing us in complex low-level topics such as process management (creating a new process for each command), manual memory handling, terminal signal management, and input/output manipulation. Building Minishell gave us a deep understanding of how a shell works while adhering to 42’s strict pedagogical constraints (rigid coding standards and autonomous learning). Collaborating on this project also strengthened our coordination skills: we had to communicate constantly, divide tasks, and leverage each other’s strengths to complete the project successfully.

## Key Learnings  
Beyond the functional result, Minishell proved to be an extremely valuable learning experience. Here are some of the key lessons we drew from it:

- **Project Architecture:** We learned to plan and organize the program into clear modules—for instance, separating command parsing from execution. This modular design improves code readability and maintainability.  
- **Precision and Reliability:** System programming in C requires great rigor. Every memory allocation is followed by proper deallocation to avoid leaks, and each system call is carefully checked. We developed a keen attention to detail to ensure Minishell operates reliably under all circumstances (no unexpected crashes, proper error handling).  
- **Pair Programming:** Working on the same codebase as a team sharpened our communication and organizational skills. We used a version control system (*Git*) to collaborate simultaneously, conduct peer code reviews, and merge our contributions without conflicts. This collaboration taught us how to delegate roles and make the most of each other’s strengths.  
- **Code Structuring:** We maintained clean and maintainable code, strictly following 42's coding standards. This included consistent naming conventions, reasonably sized and well-documented functions, and a project structure that facilitates future feature additions.

## Further Reading  
One of the project authors even wrote a **blog post** about Minishell to share insights and lessons learned. Titled *“Tips I Wish I Knew Before Starting Minishell”*, the article offers practical advice for future students tackling this project (strategies, common pitfalls, best practices, etc.). [*Si je devais recommencer minishell.*](https://medium.com/@mostafa.omrane/mes-conseils-si-je-devais-recommencer-minishell-a9783c51ba1b)

## Screenshots  
Below are some screenshots showing **Minishell** in action, demonstrating various commands and features:

- **Simple command:** Executing `pwd` to display the current working directory.  
- **Output redirection to a file:** The command `echo "Hello" > hello.txt` sends the output to a file instead of displaying it on the screen (a file named **hello.txt** is created with the content "Hello").  
- **Piping commands:** Using `ls -la | grep txt` to list all files and then filter those containing "txt". Minishell connects both commands so the output of `ls -la` becomes the input of `grep`, displaying only the matching lines.  

## Shell Features  
Minishell supports a range of **essential features** to emulate the behavior of a basic Unix shell:

- **Interactive prompt:** Displays a custom prompt waiting for user input (e.g., `minishell>`).  
- **Execution of external programs:** Launches system programs by name. The shell searches for the executable in the `$PATH` directories or executes a program directly via an absolute or relative path (e.g., `ls`, `grep`, or any available binary).  
- **Built-in commands:** Supports key built-in shell commands, including:  
  - `echo` (with `-n` to omit the trailing newline).  
  - `cd` (change the current directory).  
  - `pwd` (display the current directory).  
  - `export` (add or modify environment variables).  
  - `unset` (remove environment variables).  
  - `env` (display all environment variables).  
  - `exit` (exit the shell).  
- **Environment variables:** Supports variable expansion within commands. For example, if `$HOME` is defined, typing `echo $HOME` displays its value (the user’s home directory). The special variable `$?` is also supported, returning the exit status of the last executed command.  
- **Input/output redirection:** Handles standard input and output redirection like Bash. Input can be redirected from a file using `<`, and output can be redirected to a file using `>` (overwrite) or `>>` (append). Minishell also supports *here-document* mode (`<<`), which allows multiline input until a defined delimiter is reached.  
- **Pipes (`|`):** Supports chaining commands using *pipes*. The `|` symbol allows the output of one command to be passed as input to the next (e.g., `command1 | command2 | command3`), enabling streamlined data processing in a single line.  
- **Signal handling:** Minishell handles terminal signals to replicate standard shell behavior when interrupted via the keyboard. For example, `Ctrl+C` interrupts the current command without exiting the shell (Minishell then displays a fresh prompt), `Ctrl+D` exits the shell on an empty line (end-of-input), and `Ctrl+\` is ignored to prevent accidental termination.  
- **Error handling:** In the event of invalid commands or execution errors, Minishell displays clear error messages (e.g., *command not found*) instead of crashing. This ensures a controlled and user-friendly experience, even with incorrect inputs.

*Note: Minishell focuses on core shell features and does not implement advanced features such as conditional operators (`&&`/`||`), command separation with semicolons (`;`), or wildcards (`*` for file pattern matching).*

**Finally, Minishell’s source code fully adheres to 42’s coding standards and is free from memory leaks**—all allocated resources are properly released, ensuring the program’s stability and robustness until it exits.
