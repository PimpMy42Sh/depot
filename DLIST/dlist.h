#ifndef DLIST_H
# define DLIST_H
# include <libft/libft.h>

typedef struct		s_dlist
{
	void			*content;
	size_t			content_size;
	struct s_dlist	*next;
	struct s_dlist	*last;
}					t_dlist;

t_dlist		*ft_dlstnew(void *cnt, size_t cnt_size);
void		ft_dlstadd(t_dlist **l, t_dlist *new);
void		ft_dlstadd_end(t_dlist **ptr, t_dlist *new);
void		ft_dlstadd_begin(t_dlist **ptr, t_dlist *new);
t_dlist		*ft_lst_to_dlist(t_list *lst, int disalloc);
void		ft_dlstfree(t_dlist **dl, void (*free_cnt)());

#endif