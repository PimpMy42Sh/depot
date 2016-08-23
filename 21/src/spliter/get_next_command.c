#include <spliter.h>

/*
**	Creer a partir d'une liste de char* un tableau de char**
**	Puis ajoute notre nouvel argv dans une autre liste qui est la pipeline
*/

static void				my_pipeline(t_list **ptr, t_list **cmd)
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

static void				add_pipe(t_norme_com *n, t_command *com, t_list **tmp)
{
	if (*n->cpy)
		ft_lstadd(tmp, ft_lstnew_noalloc(n->cpy, ft_strlen(n->cpy)));
	n->cpy = ft_strnew(1024);
	n->str = (char*)n->cpy;
	my_pipeline(&com->pipeline, tmp);
	(*n->cmd)++;
}

static void				add_argument(t_norme_com *n, t_list **tmp)
{
	while (**n->cmd == ' ')
		(*n->cmd)++;
	if (*n->cpy)
		ft_lstadd(tmp, ft_lstnew_noalloc(n->cpy, ft_strlen(n->cpy)));
	n->cpy = ft_strnew(1024);
	n->str = (char*)n->cpy;
}

static void				end_gnc(t_norme_com *n, t_command *com, t_list **tmp)
{
	if (*n->cpy)
		ft_lstadd(tmp, ft_lstnew_noalloc(n->cpy, ft_strlen(n->cpy)));
	else
		free(n->cpy);
	if (tmp)
		my_pipeline(&com->pipeline, tmp);
	ft_memset(&com->redirs, 0, sizeof(t_redirections));
	if (is_a_redirection(*n->cmd))
		com->need_redir = build_redirection(&com->redirs, n->cmd);
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
	t_norme_com	n;
	t_list		*tmp;
	t_command	com;

	init_norme_com(&n, cmd);
	tmp = NULL;
	ft_memset(&com, 0, sizeof(t_command));
	while (**n.cmd && !is_a_redirection(*n.cmd))
	{
		if (**n.cmd == '|')
			add_pipe(&n, &com, &tmp);
		else if (**n.cmd != ' ')
			*(n.str++) = *((*n.cmd)++);
		else
			add_argument(&n, &tmp);
	}
	end_gnc(&n, &com, &tmp);
	return (com);
}
