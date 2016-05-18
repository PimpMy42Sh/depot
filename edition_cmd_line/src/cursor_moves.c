/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 15:05:15 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/18 16:46:48 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			move_n_char(t_it *it, int direction, int n)
{
	void (*fonction)(t_it*);

	if (direction == KL)
		fonction = move_left;
	else
		fonction = move_right;
	while (n--)
		fonction(it);
}

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
	int temp;

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
	if (!((it->i + 1) % it->ws_col))
	{
		//tputs(tgetstr("do", NULL), 0, my_putchar);
		tputs(tgetstr("sf", NULL), 0, my_putchar);
		tputs(tgetstr("cr", NULL), 0, my_putchar);
	}
	else
		tputs(tgetstr("nd", NULL), 0, my_putchar);
}

void			move_begin(t_it *it)
{
	while (it->i > it->offset)
	{
		it->i--;
		tputs(tgetstr("le", NULL), 0, my_putchar);
	}
}
