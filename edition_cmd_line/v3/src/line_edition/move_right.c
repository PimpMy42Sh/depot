/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_right.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Marco <Marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/08 09:38:28 by Marco             #+#    #+#             */
/*   Updated: 2016/07/21 17:05:45 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_if_go_down(t_it *it)
{
	if (!((it->offset + it->i + 1) % it->ws_col))
	{
		if (!it->r_video)
		{
			tputs(tgetstr(DOWN, NULL), 0, my_putchar);
			tputs(tgetstr(BEGIN, NULL), 0, my_putchar);
		}
		else
		{
			if (it->i < it->saved_i)
				tputs(tgetstr(DEFAULT, NULL), 0, my_putchar);
			ft_putchar(it->line[it->i - 1]);
			tputs(tgetstr(REVERSE, NULL), 0, my_putchar);
			tputs(tgetstr(DOWN, NULL), 0, my_putchar);
			tputs(tgetstr(BEGIN, NULL), 0, my_putchar);
		}
		return (1);
	}
	return (0);
}

static int	move_right_r_video(t_it *it)
{
	if (it->i > it->saved_i)
	{
		if (it->i == it->len)
		{
			it->i--;
			return (1);
		}
		ft_putchar(it->line[it->i - 1]);
		return (1);
	}
	else
	{
		tputs(tgetstr(DEFAULT, NULL), 0, my_putchar);
		ft_putchar(it->line[it->i - 1]);
		tputs(tgetstr(REVERSE, NULL), 0, my_putchar);
		return (1);
	}
	return (0);
}

void		move_right(t_it *it)
{
	if (it->i == it->len)
		return ;
	it->i++;
	if (check_if_go_down(it))
		return ;
	if (it->r_video)
	{
		if (move_right_r_video(it))
			return ;
	}
	tputs(tgetstr(RIGHT, NULL), 0, my_putchar);
}
