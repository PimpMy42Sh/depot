#include <dlist.h>

t_dlist		*ft_dlstnew(void *cnt, size_t cnt_size)
{
	t_dlist	*dlst;

	if ((dlst = (t_dlist*)malloc(sizeof(t_dlist))))
	{
		dlst->content = cnt;
		dlst->content_size = cnt_size;
		dlst->next = NULL;
		dlst->last = NULL;
	}
	return (dlst);
}
