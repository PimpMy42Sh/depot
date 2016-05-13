/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:48:46 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/13 14:27:17 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		resize_buffer(t_it *it)
{
	char		*tmp;
	int			i;
	static int	indice = 2;

	i = 0;
	tmp = ft_memalloc(sizeof(char) * (MAX_SIZE * indice));
	while (i < MAX_SIZE * indice - 1)
	{
		tmp[i] = it->line[i];
		i++;
	}
	tmp[i] = 0;
	ft_memdel((void**)&it->line);
	it->line = ft_strdup(tmp);
	ft_memdel((void**)&tmp);
	indice++;
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

static void		write_buffer(t_it *it, int offset)
{
	char			cmd[2];
	int				max_size;
	int				tmp;

	max_size = init_max_size(it->line);
	tmp = 0;
	if (it->buffer >= ESP && it->buffer <= TILDE)
	{
		cmd[0] = it->buffer;
		cmd[1] = '\0';
		it->i++;
		if (it->i <= max_size)
		{
			tmp = (it->i - offset) - 1;
			replace_char(it, tmp);
			it->tmp_line = ft_strdup(it->line);
		}
		else
		{
			parse_buffer(cmd, it);
			ft_putchar(it->buffer);
			it->tmp_line = ft_strdup(it->line);
		}
	}
}

void			parse_line(t_it *it)
{
	char			cmd[2];
	int				offset;

	offset = return_offset() + 2;
	if (!it->i)
		it->i = offset;
	if (it->buffer >= ESP && it->buffer <= TILDE && !it->r_video)
		write_buffer(it, offset);
	else
		edit_line(it);
}
