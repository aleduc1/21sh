#!/bin/bash

CGR='\033[0;32m'
CRE='\033[0;31m'
NO='\033[0m'

name=$1

if [ -z $name ]; then
	printf "./test.sh [executable name]"
	exit
fi
if [ ! -x $name ]; then
	printf "File $name not found"
	exit
fi
clear

printf "=============================\n"
printf "|           DEBUT           |\n"
printf "=============================\n"

if [ -z "$2" -a "$2" != "1" ]; then
	dossier="/tmp/test"
	rm -rf $dossier
	mkdir -p $dossier
	# printf "Utilisez la commande suivante pour check les leaks:\n"
	printf "Utilisez valgrind [y/N]? "
	read inputuser
	if [ "$inputuser" == "y" ]; then
		valgrind --log-file="$dossier/valgrind.log" ./test.sh $name 1 2> co
		exit
	fi
else
	dossier="/tmp/test"
fi
n=0
clear
# printf "valgrind --leak-check=full --log-file=\"$dossier/valgrind.log\" bash --posix\n\n"

printf "Make [y/N]? "
read inputuser
if [ "$inputuser" == "y" ]; then make re; fi
# clear

ft_test_basic()
{
	printf "\n\n========================\n"
	printf "Test basic\n"
	printf "========================\n"
	# Test ls
	./$name "ls" > $dossier/${n}a 2> $dossier/${n}ae
	ls > $dossier/${n}b 2> $dossier/${n}be
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "ls: ${CGR}Ok$NO\n"
	else
		printf "ls: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"

	# Test command error
	./$name "qwere" > $dossier/${n}a 2> $dossier/${n}ae
	touch $dossier/${n}b
	printf "21sh: command not found: qwere\n" > $dossier/${n}be
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "Command error: ${CGR}Ok$NO\n"
	else
		printf "Command error: ${CRE}No$NO\n\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"

	# Test option invalid: ls -z
	./$name "ls -z" > $dossier/${n}a 2> $dossier/${n}ae
	ls -z > $dossier/${n}b 2> $dossier/${n}be
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "ls -z: ${CGR}Ok$NO\n"
	else
		printf "ls -z: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"

	# Test /bin/ls
	./$name "/bin/ls -la" > $dossier/${n}a 2> $dossier/${n}ae
	/bin/ls -la > $dossier/${n}b 2> $dossier/${n}be
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "/bin/ls: ${CGR}Ok$NO\n"
	else
		printf "/bin/ls: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"

	# Test ls -la
	./$name "ls -la" > $dossier/${n}a 2> $dossier/${n}ae
	ls -la > $dossier/${n}b 2> $dossier/${n}ae
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "ls -la: ${CGR}Ok$NO\n"
	else
		printf "ls -la: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"

	# Test ls -l                -a                -f
	./$name "ls -l                -a                -f" > $dossier/${n}a 2> $dossier/${n}ae
	ls -l                -a                -f > $dossier/${n}b 2> $dossier/${n}be
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "ls -l                -a                -f: ${CGR}Ok$NO\n"
	else
		printf "ls -l                -a                -f: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"
}

ft_test_builtin()
{
	printf "\n\n========================\n"
	printf "Test builtin\n"
	printf "========================\n"

	# Test cd
	./$name "cd" "pwd" > $dossier/${n}a 2> $dossier/${n}ae
	cd && pwd > $dossier/${n}b 2> $dossier/${n}be
	cd - > /dev/null
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "Test cd: ${CGR}Ok$NO\n"
	else
		printf "Test cd: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"

	# Test cd ~
	./$name "cd ~" "pwd" > $dossier/${n}a 2> $dossier/${n}ae
	cd ~ && pwd > $dossier/${n}b 2> $dossier/${n}be
	cd - > /dev/null
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "Test cd ~: ${CGR}Ok$NO\n"
	else
		printf "Test cd ~: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"

	# Test cd -
	./$name "cd ~" "cd -" "pwd" > $dossier/${n}a 2> $dossier/${n}ae
	cd ~ && cd -  > $dossier/${n}b 2> $dossier/${n}be && pwd >> $dossier/${n}b 2>> $dossier/${n}be
	# cd - > /dev/null
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "Test cd -: ${CGR}Ok$NO\n"
	else
		printf "Test cd -: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"

	# A faire permission

	# Test printf
	./$name "printf salut" "printf \"\$TERM\"" "printf '\$TERM'" "printf \"salut: '\$TERM'\"" > $dossier/${n}a 2> $dossier/${n}ae
	printf salut > $dossier/${n}b 2> $dossier/${n}be
	printf "$TERM" >> $dossier/${n}b 2>> $dossier/${n}be
	printf '$TERM' >> $dossier/${n}b 2>> $dossier/${n}be
	printf "salut: '$TERM'" >> $dossier/${n}b 2>> $dossier/${n}be
	# cd - > /dev/null
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "Test printf: ${CGR}Ok$NO\n"
	else
		printf "Test printf: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"

	printf "Test exit"

}

ft_test_redirection()
{
	printf "\n\n========================\n"
	printf "Test redirection\n"
	printf "========================\n"

	# Test >
	./$name "printf \"Testing redirections,\" > $dossier/${n}a"
	printf "Testing redirections," > $dossier/${n}b
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	if [ -f $dossier/${n}a -a -z "$first" ]; then
		printf "Test >: ${CGR}Ok$NO\n"
	else
		printf "Test >: ${CRE}No$NO\n"
		printf "$first\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi

	# Test >>
	./$name "printf \"with multiple lines\" >> $dossier/${n}a"
	printf "with multiple lines" >> $dossier/${n}b
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	if [ -f $dossier/${n}a -a -z "$first" ]; then
		printf "Test >>: ${CGR}Ok$NO\n"
	else
		printf "Test >>: ${CRE}No$NO\n"
		printf "$first\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"

	# Test <
	./$name "wc -c < $dossier/$((n-1))a" > $dossier/${n}a  2> $dossier/${n}ae
	wc -c < $dossier/$((n-1))b > $dossier/${n}b  2> $dossier/${n}be
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "Test <: ${CGR}Ok$NO\n"
	else
		printf :"Test <: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"


	printf "Test heredoc: $CRE A faire$NO\n\n"

	# cat -e << EOF
	# Roses are red
	# Violets are blue
	# All my base are belong to you
	# And so are you
	# EOF

	# cat -e << EOF >> /tmp/test.txt
	# Roses are red
	# Violets are blue
	# All my base are belong to you
	# And so are you
	# EOF

	# Test &>
	./$name "ls . dfghjkl &> $dossier/${n}a"
	ls . dfghjkl &> $dossier/${n}b
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	if [ -f $dossier/${n}a -a -z "$first" ]; then
		printf "Test &>: ${CGR}Ok$NO\n"
	else
		printf "Test &>: ${CRE}No$NO\n"
		printf "$first\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"

	# Test >&
	./$name "ls . dfghjkl >& $dossier/${n}a"
	ls . dfghjkl >& $dossier/${n}b
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	if [ -f $dossier/${n}a -a -z "$first" ]; then
		printf "Test >&: ${CGR}Ok$NO\n"
	else
		printf "Test >&: ${CRE}No$NO\n"
		cat $dossier/${n}a
		printf "\n"
		cat $dossier/${n}b
		#printf "$first\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"

	# Test 2>&-
	./$name "rm nosuchfile 2>&-" > $dossier/${n}a 2> $dossier/${n}ae
	touch $dossier/${n}b
	touch $dossier/${n}be
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "Test 2>&-: ${CGR}Ok$NO\n"
	else
		printf "Test 2>&-: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"

	# Test 2>&1
	./$name "rm nosuchfile 2>&1 | cat -e" > $dossier/${n}a
	printf "rm: nosuchfile: No such file or directory$\n" > $dossier/${n}b
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	if [ -f $dossier/${n}a -a -z "$first" ]; then
		printf "Test 2>&1: ${CGR}Ok$NO\n"
	else
		printf "ls -la: ${CRE}No$NO\n"
		printf "$first\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"
}

ft_test_multiple_command()
{
	printf "\n\n========================\n"
	printf "Test multiple command\n"
	printf "========================\n"

	# Test multiple command
	./$name "ls -1; touch newfile; ls -1" > $dossier/${n}a  2> $dossier/${n}ae
	rm newfile
	ls -1 > $dossier/${n}b 2> $dossier/${n}be
	touch newfile
	ls -1 >> $dossier/${n}b 2>> $dossier/${n}be
	rm newfile
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "Test multiple command: ${CGR}Ok$NO\n"
	else
		printf "Test multiple command: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"
}

ft_test_pipe()
{
	printf "\n\n========================\n"
	printf "Test pipe\n"
	printf "========================\n"

	# Test simple pipe
	./$name "ls | wc" > $dossier/${n}a  2> $dossier/${n}ae
	ls | wc > $dossier/${n}b  2> $dossier/${n}be
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "Test simple pipe: ${CGR}Ok$NO\n"
	else
		printf "Test simple pipe: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"

	# Test multiple pipe
	./$name "ls -r | sort | cat -e" > $dossier/${n}a  2> $dossier/${n}ae
	ls -r | sort | cat -e > $dossier/${n}b  2> $dossier/${n}be
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "Test multiple pipe: ${CGR}Ok$NO\n"
	else
		printf "Test multiple pipe: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"

	rm -rf test
	./$name "mkdir test ; cd test ; ls -a ; ls | cat | wc -c > fifi ; cat fifi" > $dossier/${n}a  2> $dossier/${n}ae
	rm -rf test
	mkdir test
	cd test
	ls -a  > $dossier/${n}b  2> $dossier/${n}be
	ls | cat | wc -c > fifi
	cat fifi >> $dossier/${n}b  2>> $dossier/${n}be
	cd .. && rm -rf test
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "Test more complicate multiple pipe: ${CGR}Ok$NO\n"
	else
		printf "Test more complicate multiple pipe: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"

	# Test base64 /dev/urandom | head -c 1000 | wc -c
	./$name "base64 /dev/urandom | head -c 1000 | wc -c" > $dossier/${n}a  2> $dossier/${n}ae
	base64 /dev/urandom | head -c 1000 | wc -c > $dossier/${n}b  2> $dossier/${n}be
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "Test base64 /dev/urandom | head -c 1000 | wc -c: ${CGR}Ok$NO\n"
	else
		printf "Test base64 /dev/urandom | head -c 1000 | wc -c: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"
}

# cd /tmp; sort << EOF 
# Roses are red
# Violets are blue
# All my base are belong to you
# I love you
# EOF | cat -e > sorted_poem ; sed -e 's/Roses/Turnips/' < sorted_poem > better_poem; cd -; printf "I prefer turnips anyway" >> /tmp/better_poem; cat /tmp/better_poem


ft_env()
{
	printf "\n\n========================\n"
	printf "Test env\n"
	printf "========================\n"

	# Test env
	env -i ./$name "ls" > $dossier/${n}a  2> $dossier/${n}ae
	touch $dossier/${n}b
	printf "21sh: command not found: ls\n" > $dossier/${n}be
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "Test env vide ls: ${CGR}Ok$NO\n"
	else
		printf "Test env vide ls: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"

	env -i ./$name "/bin/ls" > $dossier/${n}a  2> $dossier/${n}ae
	/bin/ls > $dossier/${n}b  2> $dossier/${n}be
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "Test env vide /bin/ls: ${CGR}Ok$NO\n"
	else
		printf "Test env vide /bin/ls: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"

	env -i ./$name "ls | wc" > $dossier/${n}a  2> $dossier/${n}ae
	touch $dossier/${n}b
	printf "21sh: command not found: ls\n" > $dossier/${n}be
	printf "21sh: command not found: wc\n" >> $dossier/${n}be
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "Test env vide ls | wc: ${CGR}Ok$NO\n"
	else
		printf "Test env vide ls | wc: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"

	env -i ./$name "/bin/ls | /usr/bin/wc" > $dossier/${n}a  2> $dossier/${n}ae
	/bin/ls | /usr/bin/wc > $dossier/${n}b  2> $dossier/${n}be
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "Test env vide /bin/ls | /usr/bin/wc: ${CGR}Ok$NO\n"
	else
		printf "Test env vide /bin/ls | /usr/bin/wc: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"

	./$name "setenv" > $dossier/${n}a 2> $dossier/${n}ae
	if [ -f $dossier/${n}ae -a -s "$dossier/${n}ae" ]; then
		printf "Test setenv: ${CRE}No$NO\n"
		cat $dossier/${n}ae
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	else
		printf "Test setenv: ${CGR}Ok$NO\n"
	fi
	n=$((n+1))
	printf "\n"

	./$name "unsetenv" > $dossier/${n}a  2> $dossier/${n}ae
	if [ -f $dossier/${n}ae -a -s "$dossier/${n}ae" ]; then
		printf "Test setenv: ${CRE}No$NO\n"
		cat $dossier/${n}ae
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	else
		printf "Test setenv: ${CGR}Ok$NO\n"
	fi
	n=$((n+1))
	printf "\n"

	./$name "env" > $dossier/${n}a  2> $dossier/${n}ae
	if [ -f $dossier/${n}ae -a -s "$dossier/${n}ae" ]; then
		printf "Test setenv: ${CRE}No$NO\n"
		cat $dossier/${n}ae
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	else
		if [ -f $dossier/${n}a -a -s "$dossier/${n}a" ]; then
			printf "Test setenv: ${CGR}Ok$NO\n"
		else
			printf "Test setenv: ${CRE}No$NO\n"
			cat $dossier/${n}ae
			printf "\nQuitter [y/N]? "
			read inputuser
			if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
		fi
	fi
	n=$((n+1))
	printf "\n"

	env -i ./$name "setenv toto tata" "env"> $dossier/${n}a  2> $dossier/${n}ae
	printf "toto=tata\n" > $dossier/${n}b
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	if [ -f $dossier/${n}ae -a -s "$dossier/${n}ae" ]; then
		printf "Test add key setenv: ${CRE}No$NO\n"
		cat $dossier/${n}ae
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	else
		if [ -f $dossier/${n}a -a -z "$first" ]; then
			printf "Test add key setenv: ${CGR}Ok$NO\n"
		else
			printf "Test add key setenv: ${CRE}No$NO\n"
			echo "$first"
			printf "\nQuitter [y/N]? "
			read inputuser
			if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
		fi
	fi
	n=$((n+1))
	printf "\n"

	env -i ./$name "setenv toto tata" "unsetenv toto" "env"> $dossier/${n}a  2> $dossier/${n}ae
	touch $dossier/${n}b
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	if [ -f $dossier/${n}ae -a -s "$dossier/${n}ae" ]; then
		printf "Test add key and remove: ${CRE}No$NO\n"
		cat $dossier/${n}ae
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	else
		if [ -f $dossier/${n}a -a -z "$first" ]; then
			printf "Test add key and remove: ${CGR}Ok$NO\n"
		else
			printf "Test add key and remove: ${CRE}No$NO\n"
			cat $dossier/${n}a
			cat $dossier/${n}ae
			cat $dossier/${n}b
			cat $dossier/${n}be
			printf "\nQuitter [y/N]? "
			read inputuser
			if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
		fi
	fi
	n=$((n+1))
	printf "\n"

}

ft_path()
{
	printf "\n\n========================\n"
	printf "Test PATH\n"
	printf "========================\n"

	env -i ./$name "setenv PATH /usr/bin:/bin" "ls" "wc < author" > $dossier/${n}a  2> $dossier/${n}ae
	ls > $dossier/${n}b  2> $dossier/${n}be
	wc < author >> $dossier/${n}b  2>> $dossier/${n}be
	if [ -f $dossier/${n}a ]; then
		first=`diff $dossier/${n}a $dossier/${n}b`
	else
		first=""
	fi
	sec=`diff $dossier/${n}ae $dossier/${n}be`
	if [ -f $dossier/${n}a -a -z "$first" -a -z "$sec" ]; then
		printf "Test PATH set with setenv: ${CGR}Ok$NO\n"
	else
		printf "Test PATH set with setenv: ${CRE}No$NO\n"
		printf "$first\n"
		printf "$sec\n"
		printf "\nQuitter [y/N]? "
		read inputuser
		if [ "$inputuser" == "y" ]; then printf "Log file: $dossier/$n \n"; exit; fi
	fi
	n=$((n+1))
	printf "\n"
}

ft_test_signaux()
{
	printf "\n\n========================\n"
	printf "Test Signaux\n"
	printf "========================\n"

	printf "$CRE A faire\n\n$NO"

}

ft_test_basic
ft_test_builtin
ft_test_redirection
ft_test_multiple_command
ft_test_pipe
ft_env
ft_path
ft_test_signaux


if [ -f $dossier/valgrind.log ]; then
	printf "Check leaks:\n"
	cat /tmp/test/valgrind.log | grep -A 5 "LEAK"
fi

printf "\nTester la norme [y/N]? "
read inputuser
if [ "$inputuser" == "y" ]; then 
	norminette srcs includes libft/srcs libft/includes
	printf "\n\nAuthor:\n"
	cat author
fi
