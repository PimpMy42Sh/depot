/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 15:05:15 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/13 16:04:21 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			move_left(t_it *it, int offset)
{
	it->i--;
	if (it->i < offset)
	{
		it->i += 1;
		return ;
	}
	if (it->r_video)
	{
		ft_putchar(it->line[(it->i - return_offset() - 1)]);
		tputs(tgetstr("le", NULL), 0, my_putchar);
	}
	tputs(tgetstr("le", NULL), 0, my_putchar);
}

void			move_right(t_it *it, int offset)
{	
	it->i++;
	if (it->i > offset + (int)ft_strlen(it->line))
	{
		it->i -= 1;
		return ;
	}
	if (it->r_video)
	{
		ft_putchar(it->line[(it->i - return_offset() - 3)]);
		tputs(tgetstr("le", NULL), 0, my_putchar);
	}
	tputs(tgetstr("nd", NULL), 0, my_putchar);
}

void			del_char(t_it *it, int offset)
{
	del_char_buffer(it, offset);
	it->tmp_line = ft_strdup(it->line);
	move_left(it, offset);
	tputs(tgetstr("dc", NULL), 0, my_putchar);
}

void			move_begin(t_it *it, int offset)
{
	while (it->i > offset)
	{
		it->i--;
		tputs(tgetstr("le", NULL), 0, my_putchar);
	}
}
