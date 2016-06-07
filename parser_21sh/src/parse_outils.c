#include <parse.h>

/*
**	Creer un nouveau maillon sans allouer son contenu
*/

t_list		*ft_lstnew_noalloc(void *cnt, size_t cnt_size)
{
	t_list	*new;

	if ((new = (t_list*)malloc(sizeof(t_list))))
	{
		new->content = cnt;
		new->content_size = cnt_size;
		new->next = NULL;
	}
	else
		new = NULL;
	return (new);
}

/*
**	Equivalent a ft_lstadd
*/

void		add_cmd(t_list **ptr, t_list *new)
{
	t_list	*lst;

	if (!new->content_size)
		return ;
	if ((lst = *ptr))
	{
		while (lst->next)
			lst = lst->next;
		lst->next = new;
	}
	else
		*ptr = new;
}

/*
**	Creer les arguments a envoyer (nom de cmd compris)
**	lst: liste de commandes
*/

char		**lst_to_args(t_list *lst)
{
	char	**args;
	int		size;
	t_list	*tmp;

	size = 0;
	tmp = lst;
	while (tmp)
	{
		tmp = tmp->next;
		size++;
	}
	if ((args = (char**)malloc(sizeof(char*) * (size + 1))))
	{
		size = 0;
		while (lst)
		{
			args[size++] = (char*)lst->content;
			lst = lst->next;
		}
		args[size] = (char*)0;
	}
	else
		args = (char**)0;
	return (args);
}

/*
**	Creer les arguments a envoyer (nom de cmd compris)
**	UNIQUEMENT POUR LES PIPES
**	lst: liste de commandes
*/

char		**lst_to_pipe_args(t_list **lst)
{
	char	**args;
	int		size;
	t_list	*tmp;

	size = 0;
	tmp = *lst;
	while (tmp && tmp->content)
	{
		tmp = tmp->next;
		size++;
	}
	if ((args = (char**)malloc(sizeof(char*) * (size + 1))))
	{
		size = 0;
		tmp = *lst;
		while (tmp && tmp->content)
		{
			args[size++] = (char*)tmp->content;
			tmp = tmp->next;
		}
		args[size] = NULL;
	}
	*lst = tmp && !tmp->content ? tmp->next : tmp;
	return (args);
}

/*
**	Renvoie la derniere commande d'une liste
**	tmp: liste de commande
*/

t_list		*get_last_cmd(t_list *tmp)
{
	t_list	*ret;

	ret = NULL;
	while (tmp)
	{
		if (!tmp->content && tmp->next)
			ret = tmp->next;
		tmp = tmp->next;
	}
	return (ret);
}
