/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   selection_mode.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 10:37:19 by mfamilar          #+#    #+#             */
/*   Updated: 2016/07/21 17:04:17 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ft_move_saved(t_it *it)
{
	int target;

	if (it->i > it->saved_i)
	{
		target = it->saved_i;
		while (it->i != target)
			move_left(it);
	}
}

static void	ft_check_end_of_line(t_it *it)
{
	if (!((it->offset + it->i + 1) % it->ws_col))
	{
		it->i--;
		tputs(tgetstr(LEFT, NULL), 0, my_putchar);
		tputs(tgetstr(RIGHT, NULL), 0, my_putchar);
	}
}

static void	ft_put_back_default(t_it *it)
{
	int		length;
	int		temp;

	temp = it->i;
	tputs(tgetstr(DEFAULT, NULL), 0, my_putchar);
	length = ft_abs(it->i - it->saved_i) + 1;
	ft_move_saved(it);
	if (temp > it->saved_i)
	{
		ft_memdel((void**)&it->tmp_buffer);
		it->tmp_buffer = ft_strsub(it->line, it->i, length);
	}
	else
	{
		ft_memdel((void**)&it->tmp_buffer);
		it->tmp_buffer = ft_strsub(it->line, temp, length);
	}
	ft_putstr(it->tmp_buffer);
	it->i += ft_strlen(it->tmp_buffer);
	ft_check_end_of_line(it);
}

static void	ft_replace_video(t_it *it, int rewrite)
{
	if (rewrite)
	{
		tputs(tgetstr(REVERSE, NULL), 0, my_putchar);
		ft_putchar(it->line[it->i]);
		tputs(tgetstr(LEFT, NULL), 0, my_putchar);
	}
	else
		ft_put_back_default(it);
}

void		put_reverse(t_it *it)
{
	if (it->r_video == 0)
	{
		it->r_video = 1;
		it->saved_i = it->i;
		ft_replace_video(it, 1);
	}
	else
	{
		it->r_video = 0;
		ft_replace_video(it, 0);
	}
}
