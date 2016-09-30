#!/bin/bash
#Bin_name
bin=binairy
n=1
libft=../command/libft
make -C $libft

#Linux compil
gcc -g -I. $libft/libft.a glob_match.c main_match.c -Wall -Wextra -o $bin

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
	#echo $1 $2
	./$bin $1 $2

	if [ $? -eq $3 ]
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
launch_test 'cat' 'cat' 1

###### TEST 2
launch_test 'cat' 'cat*' 1

###### TEST 3
launch_test 'cat' '*cat' 1

###### TEST 4
launch_test 'cat' '*a' 0

###### TEST 5
launch_test 'cat' 'c*******************************' 1

###### TEST 6
launch_test 'cat' 'c*t' 1

###### TEST 7
launch_test 'cat' 'z*t' 0

############### BRACKETS #############

###### TEST 8
launch_test 'cat' '[c]at' 1

###### TEST 9
launch_test 'cat' '[c][a][t]' 1

###### TEST 10
launch_test 'cat' '[a-c][a-z][t-t]' 1

###### TEST 11
launch_test 'cat' '[z-z]' 0

###### TEST 12 (-- est invalide)
launch_test 'cat' '[c--at]' 0

###### TEST 13
launch_test 'cat' '[-]' 0

###### TEST 14 (invalide dans ordre decroissant)
launch_test 'cat' '[z-a][z-a][z-a]' 0

############### REPLACE CHAR #############

###### TEST 15
launch_test 'cat' '?at' 1

###### TEST 16
launch_test 'cat' '??' 0

###### TEST 17
launch_test 'cat' '??' 0

###### TEST 18
launch_test 'cat' '???' 1

###### TEST 19
launch_test 'cat' 'c?t' 1

############### MULTI TESTS #############

###### TEST 20
launch_test 'cat' '[c]*[t]' 1

###### TEST 21
launch_test 'cat' '[c]?[t]' 1

###### TEST 22
launch_test 'cat' '[a-?-c][a-z]*t' 1

###### TEST 23
launch_test 'cat' '*[c]?*t' 1

###### TEST 24
launch_test '42sh' "42sh"  1

###### TEST 25
launch_test 'yolo' '[-]' 0

###### TEST 26
launch_test '123456789' '[!2-9][!1]?[!3]*9' 1

###### TEST 27
launch_test 'abcdef' '?[c]*****' 0

###### TEST 28
launch_test 'cat' '[a-?-c][a-z]' 0

###### TEST 29
launch_test '?*[45454545]' '4[454545454][sh]?' 0

###### TEST 30
launch_test '0' '[]' 0

###### TEST 31
echo WTFFFFFFFFFFFFf
launch_test 'main_truc.c' '*truc*' 1

###### TEST 32
launch_test '.' '*truc*' 0

###### TEST 33
launch_test 'main_truc.c' '????_truc*' 1

###### TEST 34
launch_test 'test-it' 'test[-]it' 1

###### TEST 35
launch_test 'test--it' 'test[--][--]it' 1

###### TEST 36
arg1='*'
arg2='*'
launch_test $arg1 $arg2 1

###### TEST 37
launch_test 'student' '*[s-t]*' 1
