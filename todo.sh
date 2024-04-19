- use stat function
- replace printf in builtins by ft_putstr_fd


# on sait quoi faire pour cd
cd -
cd --
cd ---
cd ----


# faire stat pour ces tests :
"$HOMEdskjhfkdshfsd"
- soucis avec exit a regler mais pour cela il faut pouvoir lancer minishell dans minishell
cd ../../../../../../bin
../minishell #(depuis src/)


# April 19th
- in export.c, a function that print a list of sorted env variables
- check ft_atol because it's not working properly
- check if we need to protect the dup2 functions (if we need, do it)
- refactor env functions
- create a function that will return a char ** from t_env * (to be used in execve)
- each time we unset PATH, we need to update the path_list variable in our t_data structure





# Note for the future
- single command not in a child process (for example, EXPORT)