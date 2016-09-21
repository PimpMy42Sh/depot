/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/09 11:45:26 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/21 17:38:10 by Marco            ###   ########.fr       */
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

void		path_manager(t_env *env)
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
	append_item_environ(env, "PATH", path);
	ft_memdel((void**)&path);
}
