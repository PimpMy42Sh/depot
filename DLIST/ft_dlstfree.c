#include <dlist.h>

void		ft_dlstfree(t_dlist **dl, void	(*free_cnt)())
{
	t_dlist	*next;

	if (free_cnt)
	{
		while (*dl)
		{
			next = (*dl)->next;
			(*free_cnt)((*dl)->content);
			free(*dl);
			*dl = next;
		}
	}
	else
	{
		while (*dl)
		{
			next = (*dl)->next;
			free(*dl);
			*dl = next;
		}
	}
}