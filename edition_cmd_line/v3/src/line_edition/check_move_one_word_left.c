/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_move_one_word_left.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Marco <Marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/19 15:27:33 by Marco             #+#    #+#             */
/*   Updated: 2016/07/19 15:30:46 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void check_move_first_elem(t_it *it)
{
	int size;
	int i;

	i = 0;
	size = it->len + it->offset;
	if ((size % it->ws_col) == it->ws_col - 1)
	{
		tputs(tgetstr(UP, NULL), 0, my_putchar);
		while (i < it->ws_col)
		{
			tputs(tgetstr(RIGHT, NULL), 0, my_putchar);
			i++;
		}
		it->i--;
	}
}

void cursor_on_last_pos(t_it *it, int line)
{
	it->i--;
	if (it->line[it->i] == ' ')
		move_one_word_left_1(it, it->i);
	else if (it->line[it->i] != ' ')
		move_one_word_left_2(it, it->i);
	if (line == (it->i + it->offset) / it->ws_col)
		tputs(tgetstr(LEFT, NULL), 0, my_putchar);
}
