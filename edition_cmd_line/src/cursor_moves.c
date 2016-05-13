/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 15:05:15 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/13 18:05:27 by mfamilar         ###   ########.fr       */
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
	if (it->r_video)
	{
		ft_putchar(it->line[(it->i - return_offset() - 1)]);
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
	if (it->r_video)
	{
		ft_putchar(it->line[(it->i - return_offset() - 3)]);
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
