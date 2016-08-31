/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_moves_one_word_left.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 17:51:43 by mfamilar          #+#    #+#             */
/*   Updated: 2016/07/21 17:06:52 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	go_left(t_it *it)
{
	if (it->i != 0)
	{
		move_left(it);
	}
	else
	{
		if (!it->r_video)
			tputs(tgetstr(LEFT, NULL), 0, my_putchar);
		it->i--;
	}
}

void		move_one_word_left_1(t_it *it, int i)
{
	while (it->line[i] && it->line[i] == ' ')
	{
		go_left(it);
		i--;
	}
	while (it->line[i] && it->line[i] != ' ')
	{
		go_left(it);
		i--;
	}
	move_right(it);
}

void		move_one_word_left_2(t_it *it, int i)
{
	while (it->line[i] && it->line[i] != ' ')
	{
		go_left(it);
		i--;
	}
	move_right(it);
}

static void	move_one_word_left_3(t_it *it, int i)
{
	while (it->line[i] && it->line[i] != ' ')
	{
		go_left(it);
		i--;
	}
	while (it->line[i] && it->line[i] == ' ')
	{
		go_left(it);
		i--;
	}
	while (it->line[i] && it->line[i] != ' ')
	{
		go_left(it);
		i--;
	}
	move_right(it);
}

void		move_one_word_left(t_it *it)
{
	int		line;

	line = (it->i + it->offset) / it->ws_col;
	if (it->i <= 0)
		return ;
	if (it->i == it->len)
		check_move_first_elem(it);
	if (it->i == it->len)
		cursor_on_last_pos(it, line);
	else if (it->line[it->i] == ' ')
		move_one_word_left_1(it, it->i);
	else if (it->line[it->i] != ' ' && it->line[it->i - 1] != ' ')
		move_one_word_left_2(it, it->i);
	else if (it->line[it->i] != ' ' && it->line[it->i - 1] == ' ')
		move_one_word_left_3(it, it->i);
	if (it->i < 0)
	{
		while (it->i != 0)
			move_right(it);
	}
}
