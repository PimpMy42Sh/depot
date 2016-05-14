#include <dlist.h>

void	ft_dlstadd_begin(t_dlist **ptr, t_dlist *new)
{
	t_dlist	*dl;

	dl = *ptr;
	if (dl)
	{
		while (dl->last)
			dl = dl->last;
		dl->last = new;
		new->next = dl;
	}
	else
		*ptr = new;
}
