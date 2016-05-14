/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 15:05:15 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/14 13:40:50 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			move_left(t_it *it)
{
	it->i--;
	if (it->i < it->offset)
	{
		it->i += 1;
		return ;
	}
	if (it->r_video && it->i < it->saved_i)
	{
		ft_putchar(it->line[(it->i - return_offset() - 1)]);
		tputs(tgetstr("le", NULL), 0, my_putchar);
	}
	else if (it->r_video && it->i >= it->saved_i)
	{
		tputs(tgetstr("me", NULL), 0, my_putchar);
		ft_putchar(it->line[(it->i - return_offset() - 1)]);
		tputs(tgetstr("mr", NULL), 0, my_putchar);
		tputs(tgetstr("le", NULL), 0, my_putchar);
	}
	tputs(tgetstr("le", NULL), 0, my_putchar);
}

void			move_right(t_it *it)
{
	it->i++;
	if (it->i > it->offset + (int)ft_strlen(it->line))
	{
		it->i -= 1;
		return ;
	}
	if (it->r_video && it->i > it->saved_i)
	{
		ft_putchar(it->line[(it->i - return_offset() - 3)]);
		tputs(tgetstr("le", NULL), 0, my_putchar);
	}
	else if (it->r_video && it->i <= it->saved_i)
	{
		tputs(tgetstr("me", NULL), 0, my_putchar);
		ft_putchar(it->line[(it->i - return_offset() - 3)]);
		tputs(tgetstr("mr", NULL), 0, my_putchar);
		tputs(tgetstr("le", NULL), 0, my_putchar);
	}
	tputs(tgetstr("nd", NULL), 0, my_putchar);
}

void			del_char(t_it *it)
{
	del_char_buffer(it);
	it->tmp_line = ft_strdup(it->line);
	move_left(it);
	tputs(tgetstr("dc", NULL), 0, my_putchar);
}

void			move_begin(t_it *it)
{
	while (it->i > it->offset)
	{
		it->i--;
		tputs(tgetstr("le", NULL), 0, my_putchar);
	}
}
