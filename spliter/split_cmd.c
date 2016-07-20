#include <spliter.h>

/*
**	Le symbole actuel est'il une redirection (ou argregateur) ?
**	Manque la gestion d'erreur ...
*/
inline int			is_a_redirection(char *cmd) 
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
inline char			**lst_to_tab(t_list *lst)
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

/*
**	Creer a partir d'une liste de char* un tableau de char**
**	Puis ajoute notre nouvel argv dans une autre liste qui est la pipeline
*/
static inline void		my_pipeline(t_list **ptr, t_list **cmd)
{
	char	**t;
	t_list	*new;
	t_list	*add;

	add = *ptr;
	t = lst_to_tab(*cmd);
	new = ft_lstnew_noalloc(t, sizeof(t));
	if ((add = *ptr))
	{
		while (add->next)
			add = add->next;
		add->next = new;
	}
	else
		*ptr = new;
	*cmd = NULL;
}

/*
**	Renvoie la prochaine commande
**	si a la fin de l'appel on as encore des caracteres alphabetiques
**		il y a une syntax erreur
**	sinon
**		OK
**
**	cmd est l'adrress d'une chaine de caractere
**	ex:get_next_command(&cmd)
*/
t_command				get_next_command(char **cmd)
{
	char		*str;
	char		*cpy;
	t_list		*tmp;
	t_command	com;

	tmp = NULL;
	ft_memset(&com, 0, sizeof(t_command));
	cpy = ft_strnew(1024);
	str = (char*)cpy;
	while (**cmd && !is_a_redirection(*cmd) && **cmd != ';')
	{
		if (**cmd == '|')
		{
			if (*cpy)
				ft_lstadd(&tmp, ft_lstnew_noalloc(cpy, ft_strlen(cpy)));
			cpy = ft_strnew(1024);
			str = (char*)cpy;
			my_pipeline(&com.pipeline, &tmp);
			(*cmd)++;
		}
		else if (**cmd != ' ')
			*(str++) = *((*cmd)++);
		else
		{
			while (**cmd == ' ')
				(*cmd)++;
			if (*cpy)
				ft_lstadd(&tmp, ft_lstnew_noalloc(cpy, ft_strlen(cpy)));
			cpy = ft_strnew(1024);
			str = (char*)cpy;
		}
	}
	if (*cpy)
		ft_lstadd(&tmp, ft_lstnew_noalloc(cpy, ft_strlen(cpy)));
	else
		free(cpy);
	if (tmp)
		my_pipeline(&com.pipeline, &tmp);
	ft_memset(&com.redirs, 0, sizeof(t_redirections));
	if (is_a_redirection(*cmd))
	{
		build_redirection(&com.redirs, cmd);
		com.need_redir = 1;
	}
	return (com);
}
