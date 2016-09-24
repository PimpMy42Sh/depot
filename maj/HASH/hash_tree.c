/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 11:47:56 by fjacquem          #+#    #+#             */
/*   Updated: 2016/09/22 11:47:59 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void		parse_tree(t_hash_tree *tmp_tree,
	t_hash_tree *tmp_node, t_hash_tree *elem)
{
	while (tmp_tree)
	{
		tmp_node = tmp_tree;
		if (elem->indice == tmp_tree->indice)
		{
			tmp_tree = tmp_tree->equal;
			if (!tmp_tree)
				tmp_node->equal = elem;
		}
		else if (elem->indice > tmp_tree->indice)
		{
			tmp_tree = tmp_tree->right;
			if (!tmp_tree)
				tmp_node->right = elem;
		}
		else
		{
			tmp_tree = tmp_tree->left;
			if (!tmp_tree)
				tmp_node->left = elem;
		}
	}
}

void			insert_node(t_hash_tree **tree, t_list *lst)
{
	t_hash_tree *tmp_node;
	t_hash_tree *tmp_tree;
	t_hash_tree *elem;

	elem = ft_memalloc(sizeof(t_hash_tree));
	tmp_tree = *tree;
	tmp_node = NULL;
	elem->node = lst;
	elem->indice = lst->indice;
	elem->left = NULL;
	elem->right = NULL;
	elem->equal = NULL;
	if (tmp_tree)
		parse_tree(tmp_tree, tmp_node, elem);
	else
		*tree = elem;
}

char			*search_node(t_hash_tree *tree, int indice)
{
	char	*tmp;

	while (tree)
	{
		if (indice == tree->node->indice)
		{
			tmp = ft_strjoin(tree->node->path, "/");
			return (ft_strjoin(tmp, tree->node->cmd));
		}
		else if (indice > tree->node->indice)
			tree = tree->right;
		else
			tree = tree->left;
	}
	return (NULL);
}

void			reset_tree(t_hash_tree **tree)
{
	if (*tree)
	{
		reset_tree(&(*tree)->left);
		reset_tree(&(*tree)->right);		
		free((*tree)->node->path);
		free((*tree)->node);
		free(*tree);
		*tree = NULL;
	}
}