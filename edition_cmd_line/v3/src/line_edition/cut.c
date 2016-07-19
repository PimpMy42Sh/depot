/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cut.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Marco <Marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 16:49:27 by Marco             #+#    #+#             */
/*   Updated: 2016/07/19 14:49:33 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		cut_line(t_it *it)
{
	int			i;

	i = 0;
	ft_memdel((void**)&it->tmp_buffer);
	it->tmp_buffer = ft_strdup(it->line);
	while (i < it->len)
	{
		move_left(it);
		i++;
	}
	tputs(tgetstr(CLEAR, NULL), 0, my_putchar);
	ft_memdel((void**)&it->line);
}

static void		cut_selection(int begin, int end, t_it *it)
{
	char	*first;
	char	*second;
	int		lenght;

	lenght = it->len - end;
	second = ft_strsub(it->line, end + 1, lenght - 1);
	first = ft_memalloc((sizeof(char) * begin) + 1);
	ft_strncpy(first, it->line, begin);
	ft_memdel((void**)&it->line);
	it->line = ft_strjoin(first, second);
	it->len = ft_strlen(it->line);
	ft_memdel((void**)&first);
	ft_memdel((void**)&second);
}

void			ft_cut_select(t_it *it)
{
	int		length;
	int		tmp;

	tputs(tgetstr(DEFAULT, NULL), 0, my_putchar);
	it->r_video = 0;
	tmp = it->i;
	length = ft_abs(it->i - it->saved_i) + 1;
	move_begin(it);
	if (tmp > it->saved_i)
	{
		ft_memdel((void**)&it->tmp_buffer);
		it->tmp_buffer = ft_strsub(it->line, it->saved_i, length);
		cut_selection(it->saved_i, tmp, it);
	}
	else
	{
		ft_memdel((void**)&it->tmp_buffer);
		it->tmp_buffer = ft_strsub(it->line, tmp, length);
		cut_selection(tmp, it->saved_i, it);
	}
	tputs(tgetstr(CLEAR, NULL), 0, my_putchar);
	ft_putstr(it->line);
	it->i += it->len;
}
