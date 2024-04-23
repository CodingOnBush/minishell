# April 23
- "$HOMEdskjhfkdshfsd" MOSTAFA/MOS
- cd ../../../../../../bin check discord
- check if we need to protect the dup2 functions (if we need, do it)
- replace printf in builtins by ft_putstr_fd
- check for permission errors VIC
- check if there are unusual exit status errors
	- 26 OK
	- 30 OK
	- 31 OK
	- 32 OK

- cat >./outfiles/outfile01 <missing MOS
	- should print bash: ./outfiles/outfile01: No such file or directory
	- instead we print minishell: missing: No such file or directory because we check infiles before outfiles and not in the order it comes
- cat < miss > ./5455/outfile01 MOS
- 135 MOS

- repenser la partie ou on checke les infs et oufs puis ou on recupere fd_in et fd_out --> parcourir la token list de la conmande et si erreur free et exit (a adapter que l'on ait une cmd built in ou non ou plusieurs cmd)


#Note for the future
- single command not in a child process (for example, EXPORT)