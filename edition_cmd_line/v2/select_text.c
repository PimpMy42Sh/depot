/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 10:37:19 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/17 11:12:44 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		ft_move_saved(t_it *it)
{
	int target;

	if (it->i > it->saved_i)
	{
		target = it->saved_i;
		while (it->i != target)
			move_left(it);
	}
}

static void		ft_replace_vid(t_it *it, int rewrite)
{
	int		length;
	int		temp;

	if (rewrite)
	{
		tputs(tgetstr("mr", NULL), 0, my_putchar);
		ft_putchar(it->line[(it->i - return_offset() - 2)]);
		tputs(tgetstr("le", NULL), 0, my_putchar);
	}
	else
	{
		temp = it->i;
		tputs(tgetstr("me", NULL), 0, my_putchar);
		length = ft_abs(it->i - it->saved_i) + 1;
		ft_move_saved(it);
		if (temp > it->saved_i)
		{
			ft_memdel((void**)&it->tmp_buffer);
			it->tmp_buffer = ft_strsub(it->line,
				((it->i - return_offset() - 2)), length);
		}
		else
		{
			ft_memdel((void**)&it->tmp_buffer);
			it->tmp_buffer = ft_strsub(it->line,
				((temp - return_offset() - 2)), length);
		}
		ft_putstr(it->tmp_buffer);
		it->i += ft_strlen(it->tmp_buffer);
	}
}

static void		cut_selection(int begin, int end, t_it *it)
{
	char	*first;
	char	*second;
	int		lenght;

	lenght = ft_strlen(it->line) - (end - it->offset);
	second = ft_strsub(it->line, end + 1, lenght - 1);
	first = ft_memalloc((sizeof(char) * begin) + 1);
	ft_strncpy(first, it->line, begin);
	ft_memdel((void**)&it->line);
	it->line = ft_strjoin(first, second);
	ft_memdel((void**)&first);
	ft_memdel((void**)&second);
}

void			ft_cut_select(t_it *it)
{
	int		length;
	int		temp;
	int		a;
	int		b;

	tputs(tgetstr("me", NULL), 0, my_putchar);
	it->r_video = 0;
	length = ft_abs(it->i - it->saved_i) + 1;
	temp = it->i;
	a = it->i - it->offset;
	b = it->saved_i - it->offset;
	move_begin(it);
	if (temp > it->saved_i)
	{
		ft_memdel((void**)&it->tmp_buffer);
		it->tmp_buffer = ft_strsub(it->line, b, length);
		cut_selection(b, a, it);
	}
	else
	{
		ft_memdel((void**)&it->tmp_buffer);
		it->tmp_buffer = ft_strsub(it->line, a, length);
		cut_selection(a, b, it);
	}
	tputs(tgetstr("cd", NULL), 0, my_putchar);
	ft_putstr(it->line);
	it->i += ft_strlen(it->line);
}

void			put_reverse(t_it *it)
{
	if (it->i - it->offset == ft_strlen(it->line))
		return ;
	if (it->r_video == 0)
	{
		it->r_video = 1;
		it->saved_i = it->i;
		ft_replace_vid(it, 1);
	}
	else
	{
		it->r_video = 0;
		ft_replace_vid(it, 0);
	}
}
