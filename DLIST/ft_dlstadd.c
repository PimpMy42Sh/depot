#include <dlist.h>

void	ft_dlstadd(t_dlist **l, t_dlist *new)
{
	t_dlist	*tmp;

	if (*l)
	{
		tmp = (*l)->last;
		(*l)->last = new;
		new->next = (*l);
		new->last = tmp;
	}
	*l = new;
}
