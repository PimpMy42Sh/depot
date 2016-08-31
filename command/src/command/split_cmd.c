#include <command.h>

/*
**	Le symbole actuel est'il une redirection (ou argregateur) ?
**	Manque la gestion d'erreur ...
*/

int						is_a_redirection(char *cmd)
{
	return (((ft_isdigit(*cmd) || *cmd == '&') &&
				(*(cmd + 1) == '<' || *(cmd + 1) == '>') &&
				!(*(cmd + 3) == '<' || *(cmd + 3) == '>')) ||
			((*cmd == '<' || *cmd == '>') &&
			!(*(cmd + 2) == '<' || *(cmd + 2) == '>')));
}

/*
**	Transforme une liste de char * en tableau de char **
**	Utiliser pour transformer les pipelines en argv
*/

char					**lst_to_tab(t_list *lst)
{
	char	**args;
	t_list	*next;
	int		n;

	n = ft_lstsize(lst);
	args = (char**)malloc(sizeof(char*) * (n + 1));
	ft_bzero(args, sizeof(char**) * (n + 1));
	while (lst)
	{
		next = lst->next;
		args[--n] = (char*)lst->content;
		free(lst);
		lst = next;
	}
	return (args);
}
