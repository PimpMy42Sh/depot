#include <dlist.h>

static t_dlist 	*disalloc_lst_to_dlist(t_list *lst)
{
	t_dlist	*new;
	t_dlist	*ptr;
	t_dlist	*last;
	t_list	*next;

	new = NULL;
	ptr = NULL;
	last = NULL;
	while (lst)
	{
		next = lst->next;
		new = ft_dlstnew(NULL, 0);
		new->content = lst->content;
		new->content_size = lst->content_size;
		new->last = last;
		ft_dlstadd(&ptr, new);
		free(lst);
		last = new;
		lst = next;
	}
	return (ptr);
}

static t_dlist	*nodisalloc_lst_to_dlist(t_list *lst)
{
	t_dlist	*new;
	t_dlist	*ptr;
	t_dlist	*last;

	new = NULL;
	ptr = NULL;
	last = NULL;
	while (lst)
	{
		new = ft_dlstnew(NULL, 0);
		new->content = lst->content;
		new->content_size = lst->content_size;
		new->last = last;
		ft_dlstadd(&ptr, new);
		last = new;
		lst = lst->next;
	}
	return (ptr);
}

t_dlist			*ft_lst_to_dlist(t_list *lst, int disalloc)
{
	t_dlist	*ptr;

	if (disalloc)
		ptr = disalloc_lst_to_dlist(lst);
	else
		ptr = nodisalloc_lst_to_dlist(lst);
	return (ptr);
}
