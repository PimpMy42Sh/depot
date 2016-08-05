/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_moves.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 15:05:15 by mfamilar          #+#    #+#             */
/*   Updated: 2016/08/05 18:14:44 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	move_n_char(t_it *it, int direction, int n)
{
	void (*fonction)(t_it*);

	if (direction == KL)
		fonction = move_left;
	else
		fonction = move_right;
	while (n--)
		fonction(it);
}

void	move_end(t_it *it)
{
	int delta;

	delta = it->len - it->i;
	move_n_char(it, KR, delta);
}

void	move_begin(t_it *it)
{
	int tmp;

	tmp = it->buffer;
	it->buffer = ALT_UP;
	while (it->i != 0)
		move_up_and_down(it);
	it->buffer = tmp;
}

void	move_up_and_down(t_it *it)
{
	if (it->buffer == ALT_UP)
	{
		if (it->i - (it->ws_col + 1) > 0)
		{
			tputs(tgetstr(UP, NULL), 0, my_putchar);
			it->i -= it->ws_col;
		}
		else
			move_n_char(it, KL, it->ws_col);
	}
	else if (it->buffer == ALT_DOWN)
	{
		if (it->i + (it->ws_col + 1) < it->len)
		{
			tputs(tparm(tgetstr(DOWN_MAJ, NULL), 1), 0, my_putchar);
			it->i += it->ws_col;
		}
		else
			move_n_char(it, KR, it->ws_col);
	}
}
