/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_moves_one_word_left.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/02 17:51:43 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/18 16:11:07 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		go_left(t_it *it)
{
	if (!(it->i == it->offset))
		move_left(it);
	else
	{
		tputs(tgetstr("le", NULL), 0, my_putchar);
		it->i--;
	}
}

static void		move_one_word_left_1(t_it *it, int i)
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
	tputs(tgetstr("nd", NULL), 0, my_putchar);
	it->i++;
}

static void		move_one_word_left_2(t_it *it, int i)
{
	while (it->line[i] && it->line[i] != ' ')
	{
		go_left(it);
		i--;
	}
	tputs(tgetstr("nd", NULL), 0, my_putchar);
	it->i++;
}

static void		move_one_word_left_3(t_it *it, int i)
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
	tputs(tgetstr("nd", NULL), 0, my_putchar);
	it->i++;
}

void			move_one_word_left(t_it *it)
{
	int		i;

	i = ((it->i - it->offset) - 1) + 1;
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
