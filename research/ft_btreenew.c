#include <btree.h>

t_btree				*ft_btreenew(const void *cnt, size_t cnt_size)
{
	t_btree	*new;

	if ((new = (t_btree*)malloc(sizeof(t_btree))))
	{
		if (cnt && cnt_size)
		{
			new->content = malloc(cnt_size);
			ft_memcpy(new->content, cnt, cnt_size);
			new->content_size = cnt_size;
		}
		else
		{
			new->content = (void*)cnt;
			new->content_size = cnt_size;
		}
		new->left = NULL;
		new->right = NULL;
	}
	return (new);
}

t_btree				*ft_btreenew_noalloc(const void *cnt, size_t cnt_size)
{
	t_btree	*new;

	if ((new = (t_btree*)malloc(sizeof(t_btree))))
	{
		new->content = (void*)cnt;
		new->content_size = cnt_size;
		new->left = NULL;
		new->right = NULL;
	}
	return (new);
}