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
- check ft_atol because it's not working properly
- check if we need to protect the dup2 functions (if we need, do it)
- create a function that will return a char ** from t_env * (to be used in execve)


# ===== April 22th =====
# ======== DONE ========
- create a function that will return a char ** from t_env * (to be used in execve)
- use THE "stat" function in ft_execve function

# ======== TODO ========
#cd - (print oldpwd and go in it)
#cd -- (do not print oldpwd and go in it)
#cd --- and more (print error) 
	#bash: cd: --: invalid option
	#cd: usage: cd [-L|[-P [-e]] [-@]] [dir]
- check ft_atol because it's not working properly
- check if we need to protect the dup2 functions (if we need, do it)
- replace printf in builtins by ft_putstr_fd



- export GHOST=123 | env | grep GHOST
	# echo $? (should be 1) because these commands are in a child process so env | grep GHOST will not find GHOST



# Note for the future
- single command not in a child process (for example, EXPORT)