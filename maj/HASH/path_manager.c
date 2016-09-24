/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 11:45:26 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/23 14:40:14 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	file_word_counter(void)
{
	char	c;
	int		i;
	int		fd;

	if ((fd = open("/etc/paths", O_RDONLY)) == -1)
		return (0);
	i = 0;
	while (read(fd, &c, 1))
		i++;
	close(fd);
	return (i);
}

void		path_manager(t_env *env, int copy)
{
	int		fd;
	char	*line;
	char	*path;

	if (!(fd = file_word_counter()))
		return ;
	path = (char*)ft_memalloc((sizeof(char) * (fd + 1)));
	fd = open("/etc/paths", O_RDONLY);
	while (get_next_line(fd, &line) > 0)
	{
		ft_strcat(path, line);
		ft_strcat(path, ":");
		ft_memdel((void**)&line);
	}
	close(fd);
	ft_memdel((void**)&line);
	path[ft_strlen(path) - 1] = 0;
	if (copy)
		append_item_environ(env, "PATH", path);
	env->etc_path = ft_strdup(path);
	ft_memdel((void**)&path);
}

void		update_hash(t_env *env)
{
	t_hash_tree		*tree;
	int				i;
	char			*path;
	char			**all_path;

	tree = ft_stock_tree(0);
	reset_tree(&tree);
	ft_stock_tree((t_hash_tree*)-1);
	if ((path = return_env(env->environ, "PATH")))
	{
		all_path = ft_strsplit(path, ':');
		ft_memdel((void**)&path);
		while (all_path[i])
		{
			file_counter(all_path[i]);
			i++;
		}
		free_double_array(all_path);
	}
}