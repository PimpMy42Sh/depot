/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_left.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Marco <Marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 09:31:55 by Marco             #+#    #+#             */
/*   Updated: 2016/07/21 17:02:38 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	move_left_r_video(t_it *it)
{
	if ((((it->offset + it->i + 3) % it->ws_col) == 0))
	{
		if (it->i > it->saved_i)
			tputs(tgetstr(DEFAULT, NULL), 0, my_putchar);
		ft_putchar(it->line[it->i + 1]);
		tputs(tgetstr(LEFT, NULL), 0, my_putchar);
		return (1);
	}
	if (it->i < it->saved_i)
	{
		ft_putchar(it->line[it->i + 1]);
		tputs(tgetstr(LEFT, NULL), 0, my_putchar);
	}
	else
	{
		tputs(tgetstr(DEFAULT, NULL), 0, my_putchar);
		ft_putchar(it->line[it->i + 1]);
		tputs(tgetstr(REVERSE, NULL), 0, my_putchar);
		tputs(tgetstr(LEFT, NULL), 0, my_putchar);
	}
	return (0);
}

void		move_left(t_it *it)
{
	int counter;

	counter = 0;
	if (it->i == 0)
		return ;
	it->i--;
	if (it->r_video)
	{
		if (move_left_r_video(it))
			return ;
	}
	if ((((it->offset + it->i + 2) % it->ws_col) == 0) &&
			!ft_isprint(it->buffer))
	{
		tputs(tgetstr(UP, NULL), 0, my_putchar);
		while (counter < it->ws_col - 1)
		{
			counter++;
			tputs(tgetstr(RIGHT, NULL), 0, my_putchar);
		}
	}
	else
		tputs(tgetstr(LEFT, NULL), 0, my_putchar);
}
