/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hachage.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 11:45:34 by mfamilar          #+#    #+#             */
/*   Updated: 2016/06/09 11:45:36 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_hash_tree			*ft_stock_tree(t_hash_tree *tree)
{
	static t_hash_tree	*tmp = NULL;

	if (tree)
		tmp = tree;
	return (tmp);
}

static t_list		*create_list(char *cmd, char *path, int indice)
{
	t_list	*new;

	new = ft_memalloc(sizeof(t_list));
	new->cmd = ft_strdup(cmd);
	new->path = ft_strdup(path);
	new->indice = indice;
	return (new);
}

static void			file_counter(char *path)
{
	int				indice;
	struct dirent	*dptr;
	DIR				*dp;
	t_list			*new;
	t_hash_tree		*tree;

	tree = ft_stock_tree(NULL);
	new = NULL;
	indice = 0;
	if (!(dp = opendir(path)))
		return ;
	while ((dptr = readdir(dp)) != NULL)
	{
		if (ft_strcmp(dptr->d_name, ".") && ft_strcmp(dptr->d_name, ".."))
		{
			indice = ft_hash(dptr->d_name);
			new = create_list(dptr->d_name, path, indice);
			insert_node(&tree, new);
		}
	}
	closedir(dp);
	ft_stock_tree(tree);
}

void				parse_path_directories(char **env)
{
	char	**all_path;
	char	*path;
	int		i;

	i = 0;
	path = return_env(env, "PATH");
	all_path = ft_strsplit(path, ':');
	ft_memdel((void**)&path);
	while (all_path[i])
	{
		file_counter(all_path[i]);
		i++;
	}
	free_double_array(all_path);
}
