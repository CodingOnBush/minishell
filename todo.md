# April 23
- "$HOMEdskjhfkdshfsd"
- cd ../../../../../../bin
- check ft_atol because it's not working properly
- check if we need to protect the dup2 functions (if we need, do it)
- replace printf in builtins by ft_putstr_fd
- export GHOST=123 | env | grep GHOST
	# echo $? (should be 1) because these commands are in a child process so env | grep GHOST will not find GHOST
- enlever ^C quand je fais Ctrl + C
- echo < 123 puis ls | exit (will echo $? 1 because echo < 123 will not work)


#Note for the future
- single command not in a child process (for example, EXPORT)