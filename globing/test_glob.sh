#!/bin/bash
#Bin_name
bin=binary
n=1
libft=../command/libft
make -C $libft
#Linux compil
gcc -g -I. glob_replace.c glob_match.c main_glob.c $libft/libft.a -Wall -Wextra -o $bin

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
	#echo $1
	./$bin $1

	if [ $? -eq 1 ]
	then
		echo -e '\033[0;32m'"TEST $n OK" '\033[0m'
	else
		echo -e '\033[0;31m'"TEST $n FAIL: ret = $?, args = $1, $2" '\033[0m'	
	fi
	n=$((n+1))
}

## ATTENTION: CERTAINS PATTERN FONT LE GLOBBING INVOLONTAIREMENT
## JE NE SAIS PAS COMMENT EMPECHER CELA
## L'ERREUR EST: (en general...) "Bad args" (s'il n'y a que des char de globbing)


################# WILDCARD ################ 

###### TEST 1
launch_test 'cat'

###### TEST 2
launch_test 'cat*'

###### TEST 3
launch_test '*cat'

###### TEST 4
launch_test '*a'

###### TEST 5
launch_test 'c*******************************'

###### TEST 6
launch_test 'c*t'

###### TEST 7
launch_test 'z*t'

############### BRACKETS #############

###### TEST 8
launch_test '[c]at'

###### TEST 9
launch_test '[c][a][t]'

###### TEST 10
launch_test '[a-c][a-z][t-t]'

###### TEST 11
launch_test '[z-z]'

###### TEST 12 (-- est invalide)
launch_test '[c--at]'

###### TEST 13
launch_test '[-]'

###### TEST 14 (invalide dans ordre decroissant)
launch_test 'cat' '[z-a][z-a][z-a]'

############### REPLACE CHAR #############

###### TEST 15
launch_test '?at'

###### TEST 16
launch_test  '??'

###### TEST 17
launch_test '??'

###### TEST 18
launch_test '???'

###### TEST 19
launch_test 'c?t'

############### MULTI TESTS #############

###### TEST 20
launch_test '[c]*[t]'

###### TEST 21
launch_test '[c]?[t]'

###### TEST 22
launch_test '[a-?-c][a-z]*t'

###### TEST 23
launch_test '*[c]?*t'

###### TEST 24
launch_test "42sh"

###### TEST 25
launch_test '[-]'

###### TEST 26
launch_test '[!2-9][!1]?[!3]*9'

###### TEST 27
launch_test '?[c]*****'

###### TEST 28
launch_test '[a-?-c][a-z]'

###### TEST 29
launch_test '4[454545454][sh]?'

###### TEST 30
launch_test '[]'