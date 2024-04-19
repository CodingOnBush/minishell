# after lunch
- use stat function
- replace printf in builtins by ft_putstr_fd
- refactor env functions

# TODO
cd ../../../../../../bin
../minishell #(depuis src/)

# Pour pwd, on a le choix entre ignorer les arguments (donc executer pwd)
# ou les considerer comme une erreur (ne pas executer pwd et avoir le bon msg d'erreur et le bon exit code)
pwd -p
pwd --p
pwd ---p
pwd -- p

# on sait quoi faire pour cd
cd -
cd --
cd ---
cd ----

# on sait comment faire avec la fonction stat()
"$HOMEdskjhfkdshfsd"

#soucis avec exit a regler mais pour cela il faut pouvoir lancer minishell dans minishell

#echo
quand on lance echo il reste en pause sans reafficher le prompt "minispell"
Je pense que c'est parce que les single commands on les a mises dans un fork et donc qu'il faut exit l'enfant
pour que le prompt revienne mais j'ai essaye et ca marche pas

# DONE
echo $""HOME
echo $""
echo $''HOME
echo $"HOME"
echo $'HO''ME'
echo $'HOME'
echo $"HOLA"
echo $"HO""ME"
echo $'HOLA'
echo "" $HOME
echo '' $HOME
echo "" hola
echo ""             hola
echo "$DONTEXIST" "Makefile"
$HOME
cd $HOME $HOME
[minispell] > cat Makefile >outf
	cat: outf: input file is output file








# April 19th
- in export.c, a function that print a list of sorted env variables
- check ft_atol because it's not working properly