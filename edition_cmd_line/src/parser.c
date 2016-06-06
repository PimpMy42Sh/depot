/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:48:46 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/17 16:28:02 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		resize_buffer(t_it *it)
{
	char		*tmp;
	int			i;

	i = 0;
	tmp = ft_memalloc(sizeof(char) * ft_strlen(it->line) * (MAX_SIZE + 1));
	while (i < ft_strlen(it->line))
	{
		tmp[i] = it->line[i];
		i++;
	}
	tmp[i] = 0;
	ft_memdel((void**)&it->line);
	it->line = ft_strdup(tmp);
	ft_memdel((void**)&tmp);
}

static void		parse_buffer(char *cmd, t_it *it)
{
	char		*tmp;

	if (!it->line)
		it->line = ft_memalloc(sizeof(char) * MAX_SIZE);
	if ((it->line[MAX_SIZE - 1]) != 0)
		resize_buffer(it);
	tmp = ft_strdup(it->line);
	ft_memdel((void**)&it->line);
	it->line = ft_strjoin(tmp, cmd);
	ft_memdel((void**)&tmp);
}

static int		init_max_size(char *line)
{
	int		max_size;
	int		offset;

	offset = return_offset() + 2;
	if (line)
		max_size = offset + ft_strlen(line);
	else
		max_size = offset;
	return (max_size);
}

static void		write_buffer(t_it *it)
{
	char			cmd[2];
	int				max_size;
	int				tmp;

	max_size = init_max_size(it->line);
	tmp = 0;
	cmd[0] = it->buffer;
	cmd[1] = '\0';
	if (it->i < max_size)
	{
		tmp = (it->i - it->offset);
		replace_char(it, tmp);
		move_right(it);
		ft_memdel((void**)&it->tmp_line);
		it->tmp_line = ft_strdup(it->line);
	}
	else
	{
		parse_buffer(cmd, it);
		multi_line_text(it);
		move_right(it);
		ft_memdel((void**)&it->tmp_line);
		it->tmp_line = ft_strdup(it->line);
	}
}

void			get_cursor_position(t_it *it)
{
	int		fd;
	char	buffer[100];

	fd = open("/dev/tty", O_RDWR);
	ft_putstr_fd(CURS_POS, fd);
	read(fd, buffer, 101);
	printf("buffer = %s\n", buffer);
	close(fd);

}

void			parse_line(t_it *it)
{
	char			cmd[2];

	it->offset = return_offset() + 2;
	if (!it->i)
		it->i = it->offset;
	if (it->buffer >= ESP && it->buffer <= TILDE && !it->r_video)
	{
		//get_cursor_position(it);
		write_buffer(it);
	}
	else
		edit_line(it);
}
