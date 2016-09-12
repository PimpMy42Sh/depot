#include <command.h>

char		*ft_strword(char *s)
{
	int		index;
	char	*new_word;
	char	*cpy;

	new_word = 0;
	index = 0;
	cpy = 0;
	while (*s == ' ')
		s++;
	cpy = s;
	while (*s != ' ' && *s != '|' && *s != '<' && *s != '>' && *s != ';' && *s)
	{
		index++;
		s++;
	}
	new_word = ft_strnew(index + 2);
	if (index)
		ft_strncpy(new_word, cpy, index);
	return (new_word);
}

t_list		*ft_lstnew_noalloc(void *cnt, size_t cnt_size)
{
	t_list	*lst;

	if ((lst = (t_list*)malloc(sizeof(t_list))))
	{
		lst->next = NULL;
		lst->content = cnt;
		lst->content_size = cnt_size;
	}
	else
		lst = NULL;
	return (lst);
}

int			ft_lstsize(t_list *t)
{
	int		n;

	n = 0;
	while (t)
	{
		n++;
		t = t->next;
	}
	return (n);
}

void		ft_lstadd_end(t_list **addr, t_list *lst)
{
	t_list	*tmp;

	if ((tmp = *addr))
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = lst;
	}
	else
		*addr = lst;
}

/*
**	Transforme une liste de char * en tableau de char **
**	Utiliser pour transformer les pipelines en argv
*/

char		**lst_to_tab(t_list *lst)
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
