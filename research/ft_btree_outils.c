#include <btree.h>

void				ft_btreeadd(t_btree **root, t_btree *new, int (*cmp)())
{
	int		ret;

	if (*root)
	{
		ret = (*cmp)(new->content, (*root)->content);
		if (ret > 0)
			ft_btreeadd(&(*root)->left, new, cmp);
		else
			ft_btreeadd(&(*root)->right, new, cmp);
	}
	else
		*root = new;
}

t_btree				*ft_btreeget(t_btree *root, void *data, int (*cmp)())
{
	int	ret;

	if (root)
	{
		ret = (*cmp)(data, root->content);
		if (ret > 0)
			return (ft_btreeget(root->left, data, cmp));
		else if (ret < 0)
			return (ft_btreeget(root->right, data, cmp));
		else
			return (root);
	}
	return (NULL);
}

t_list				*ft_lstnew_noalloc(void *cnt, size_t cnt_size)
{
	t_list	*new;

	if ((new = (t_list*)malloc(sizeof(t_list))))
	{
		new->content = cnt;
		new->content_size = cnt_size;
		new->next = NULL;
	}
	else
		new = NULL;
	return (new);
}

t_list				*ft_btreeget_all(t_list **res, t_btree *root, void *data, int (*cmp)())
{
	int	ret;

	if (root)
	{
		ret = (*cmp)(data, root->content, root->content_size);
		if (ret >= 0)
			ft_btreeget_all(res, root->left, data, cmp);
		else if (ret <= 0)
			ft_btreeget_all(res, root->right, data, cmp);
		if (!ret)
			ft_lstadd(res, ft_lstnew_noalloc(root->content, root->content_size));
	}
	return (*res);
}

void				ft_btreedel(t_btree *root, void (*del)())
{
	if (root)
	{
		if (del)
			(*del)(root->content);
		ft_btreedel(root->left, del);
		ft_btreedel(root->right, del);
		free(root);
	}
}

t_list				*ft_btreecmp_all(t_list **res, t_btree *root, t_btree *data, int (*cmp)())
{
	int	ret;

	if (root)
	{
		ret = (*cmp)(data->content, root->content, data->content_size);
		if (ret >= 0)
			ft_btreecmp_all(res, root->left, data, cmp);
		if (ret <= 0)
			ft_btreecmp_all(res, root->right, data, cmp);
		if (!ret)
			ft_lstadd(res, ft_lstnew_noalloc(root->content, root->content_size));
	}
	return (*res);
}
