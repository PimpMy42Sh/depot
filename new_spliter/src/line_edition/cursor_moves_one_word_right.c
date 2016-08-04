/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_moves_one_word_right.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:47:19 by mfamilar          #+#    #+#             */
/*   Updated: 2016/07/11 18:48:50 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void		move_one_word_right_1(t_it *it, int i)
{
	while (it->line[i] && it->line[i] == ' ')
	{
		move_right(it);
		i++;
	}
}

static void		move_one_word_right_2(t_it *it, int i)
{
	while (it->line[i] && it->line[i] != ' ')
	{
		move_right(it);
		i++;
	}
	move_one_word_right_1(it, i);
}

void			move_one_word_right(t_it *it)
{
	if (it->i >= it->len)
		return ;
	if (it->line[it->i] == ' ')
		move_one_word_right_1(it, it->i);
	else if (it->line[it->i] != ' ')
		move_one_word_right_2(it, it->i);
}
