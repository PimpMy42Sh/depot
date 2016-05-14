#include <dlist.h>

void	ft_dlstadd_end(t_dlist **ptr, t_dlist *new)
{
	t_dlist	*dl;

	dl = *ptr;
	if (dl)
	{
		while (dl->next)
			dl = dl->next;
		dl->next = new;
		new->last = dl;
	}
	else
		*ptr = new;
}
