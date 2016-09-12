#include <command.h>

/*
**	Le symbole actuel est'il une redirection (ou argregateur) ?
**
**	s:	chaine a verifier
*/

int						is_a_redirection(char *cmd)
{
	while (ft_isdigit(*cmd))
		cmd++;
	return (*cmd == '>' || *cmd == '<');
}

/*
**	Le symbole actuel est'il un caractere speciale ?
**
**	c:	caractere verifier
*/

int						is_a_spec_char(int c)
{
	return (c == '|' || c == '<' || c == '>' || c == ';');
}
