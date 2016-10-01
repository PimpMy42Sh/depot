#!/bin/bash
#Bin_name
bin=binairy
n=1
libft=../command/libft
make -C $libft
#Linux compil gcc -g -I. deps.c glob_listing.c glob.c glob_match.c main_glob.c ../command/libft/libft.a -Wall -Wextra -o binairy

gcc -g -I. deps.c glob_listing.c glob.c glob_match.c main_glob.c $libft/libft.a -Wall -Wextra -o $bin

## Creer un nouveau test
#
#	launch_test(arg1, arg2, ret)
#
# arg1 : chaine a matcher
# arg2 : chaine glob
# ret : 1 - dois matcher
#       0 - ne dois pas matcher
##

function launch_test()
{
	echo $1
	./$bin $1

	if [ $? -eq 1 ]
	then
		echo -e '\033[0;32m'"TEST $n OK" '\033[0m'
	else
		echo -e '\033[0;31m'"TEST $n FAIL: ret = $?, args = $1, $2" '\033[0m'	
	fi
	n=$((n+1))
}

###### TEST 1
match='*match*'
launch_test $match

###### TEST 2
match='*match'
launch_test $match

###### TEST 3
match='*main_*'
launch_test $match

###### TEST 4
match='*main*_*.sh'
launch_test $match

###### TEST 5
match='binar[!z]'
launch_test $match

###### TEST 6
match='[a-z]inary'
launch_test $match

###### TEST 7
match='[a---------------------------]inairy'
launch_test $match

###### TEST 8
match='[a---------------------------z]inairy'
launch_test $match

###### TEST 9
match='[a--------------------------z]inairy'
launch_test $match

###### TEST 10
match='[a-------------------------z]inairy'
launch_test $match

###### TEST 11
match='[a------------------------z]inairy'
launch_test $match

###### TEST 12
match='[a-----------------------z]inairy'
launch_test $match

###### TEST 13
match='[a----------------------z]inairy'
launch_test $match

###### TEST 14
match='[z-a]inairy'
launch_test $match

###### TEST 15
match='[!z-a]inairy'
launch_test $match

###### TEST 16 (tout les sh sauf celui ci ... bug???)
match='*.sh'
launch_test $match

###### TEST 17
match='/bin/ls'
launch_test $match

###### TEST 18
match='../*'
launch_test $match

###### TEST 19
match='ls'
launch_test $match

###### TEST 20
match='/*/*/*'
launch_test $match
