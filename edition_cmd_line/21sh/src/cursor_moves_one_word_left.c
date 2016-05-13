/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_moves_one_word_left.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 17:51:43 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/13 17:12:23 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		move_one_word_left_1(t_it *it, int i)
{
	while (it->line[i] && it->line[i] == ' ')
	{
		move_left(it, return_offset() + 2);
		i--;
	}
	while (it->line[i] && it->line[i] != ' ')
	{
		move_left(it, return_offset() + 2);
		i--;
	}
	move_right(it, return_offset() + 2);
	//tputs(tgetstr("nd", NULL), 0, my_putchar);
	//it->i++;
}

static void		move_one_word_left_2(t_it *it, int i)
{
	while (it->line[i] && it->line[i] != ' ')
	{
		move_left(it, return_offset() + 2);
		i--;
	}
	move_right(it, return_offset() + 2);
	//tputs(tgetstr("nd", NULL), 0, my_putchar);
	//it->i++;
}

static void		move_one_word_left_3(t_it *it, int i)
{
	while (it->line[i] && it->line[i] != ' ')
	{
		move_left(it, return_offset() + 2);
		i--;
	}
	while (it->line[i] && it->line[i] == ' ')
	{
		move_left(it, return_offset() + 2);
		i--;
	}
	while (it->line[i] && it->line[i] != ' ')
	{
		move_left(it, return_offset() + 2);
		i--;
	}
	move_right(it, return_offset() + 2);
	//tputs(tgetstr("nd", NULL), 0, my_putchar);
	//it->i++;
}

void			move_one_word_left(t_it *it, int offset)
{
	int		i;

	i = ((it->i - offset) - 1) + 1;
	if (i <= 0)
		return ;
	if (i == ft_strlen(it->line))
	{
		i--;
		it->i--;
		if (it->line[i] == ' ')
			move_one_word_left_1(it, i);
		else if (it->line[i] != ' ')
			move_one_word_left_2(it, i);
		tputs(tgetstr("le", NULL), 0, my_putchar);
	}
	else if (it->line[i] == ' ')
		move_one_word_left_1(it, i);
	else if (it->line[i] != ' ' && it->line[i - 1] != ' ')
		move_one_word_left_2(it, i);
	else if (it->line[i] != ' ' && it->line[i - 1] == ' ')
		move_one_word_left_3(it, i);
}
