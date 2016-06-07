#ifndef BTREE_H
# define BTREE_H
# include <stdlib.h>
# include <libft.h>
# include <stdio.h>

typedef struct		s_btree
{
	void			*content;
	size_t			content_size;
	struct s_btree	*left;
	struct s_btree	*right;	
}					t_btree;

t_btree				*ft_btreenew(const void *cnt, size_t cnt_size);
t_btree				*ft_btreenew_noalloc(const void *cnt, size_t cnt_size);
void				ft_btreeadd(t_btree **root, t_btree *new, int (*cmp)());
t_btree				*ft_btreeget(t_btree *root, void *data, int (*cmp)());
t_list				*ft_btreeget_all(t_list **result, t_btree *root, void *data, int (*cmp)());
t_list				*ft_btreecmp_all(t_list **result, t_btree *root, t_btree *data, int (*cmp)());
void				ft_btreedel(t_btree *root, void (*del)());

#endif