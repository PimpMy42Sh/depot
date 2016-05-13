/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_moves_one_word_right.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:47:19 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/13 17:01:35 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		move_one_word_right_1(t_it *it, int i)
{
	while (it->line[i] && it->line[i] == ' ')
	{
		move_right(it, return_offset() + 2);
		i++;
	}
}

static void		move_one_word_right_2(t_it *it, int i)
{
	while (it->line[i] && it->line[i] != ' ')
	{
		move_right(it, return_offset() + 2);
		i++;
	}
	move_one_word_right_1(it, i);
}

void			move_one_word_right(t_it *it, int offset)
{
	int		i;

	i = ((it->i - offset) - 1) + 1;
	if (i >= (offset + ft_strlen(it->line)))
		return ;
	if (it->line[i] == ' ')
		move_one_word_right_1(it, i);
	else if (it->line[i] != ' ')
		move_one_word_right_2(it, i);
}
