
//gcc -Wall -Wextra -I. -I.. -I../../DLIST -I../../PARSER ../../DLIST/*.c ../../PARSER/*.c *.c -lft

#include "../minishell.h"
#include <adaptation.h>
#include "../../DLIST/dlist.h"
#include "../../PARSER/grammar.h"
#define DEGUB_STR "/bin/ls -l | /bin/cat -e"
#include <string.h> 
/*
** Pas de multi-pipe :(
*/
int			main(int argc, char **argv, char **environ)
{
	t_term t;

	t.env = environ;
	if (argc == 2)
		return (parse(&t, argv[1]));
//	return (test_simple_redirection(environ));
	return (0);
	(void)t;
	(void)argc;
	(void)argv;
	(void)environ;
}
