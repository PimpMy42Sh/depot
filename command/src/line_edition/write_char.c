/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_char.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:48:46 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/20 10:16:49 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void		resize_buffer(t_it *it)
{
	char		*tmp;
	int			i;

	i = 0;
	tmp = ft_memalloc(sizeof(char) * (it->len + 1) * (MAX_SIZE + 1));
	while (i < (it->len + 1))
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

static int		init_max_size(char *line, t_it *it)
{
	int		max_size;

	if (line)
		max_size = it->len;
	else
		max_size = 0;
	return (max_size);
}

static void		write_buffer(t_it *it)
{
	char			cmd[2];
	int				max_size;

	max_size = init_max_size(it->line, it);
	cmd[0] = it->buffer;
	cmd[1] = '\0';
	if (it->i + 1 <= max_size)
	{
		replace_char(it, cmd);
		ft_memdel((void**)&it->tmp_line);
		it->tmp_line = ft_strdup(it->line);
	}
	else
	{
		parse_buffer(cmd, it);
		multi_line_text(it);
		if (!((it->offset + it->i + 2) % it->ws_col))
			tputs(tgetstr(DOWN, NULL), 0, my_putchar);
		ft_memdel((void**)&it->tmp_line);
		it->tmp_line = ft_strdup(it->line);
	}
}

void			parse_line(t_it *it)
{
	if (!it->eof)
		it->offset = return_offset();
	else
		it->offset = 1;
	if (!it->line)
	{
		it->i = 0;
		it->len = 0;
		it->nb_current_line = 0;
	}
	if (it->buffer >= ESP && it->buffer <= TILDE && !it->r_video)
	{
		write_buffer(it);
		it->i++;
		it->len++;
	}
	else
		edit_line(it);
}
