/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 11:10:43 by mfamilar          #+#    #+#             */
/*   Updated: 2016/08/25 14:13:45 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		multi_line_text(t_it *it)
{
	int	start;

	start = it->len - it->i;
	move_begin(it);
	tputs(tgetstr(CLEAR, NULL), 0, my_putchar);
	ft_putstr(it->line);
	it->i = it->len;
	if (!ft_isprint(it->buffer) && it->buffer != CTRL_D && it->buffer != DEL)
	{
		if (!((it->offset + it->i + 1) % it->ws_col))
			tputs(tgetstr(DOWN, NULL), 0, my_putchar);
	}
	if (it->buffer != KU && it->buffer != KD)
		move_n_char(it, KL, start);
	it->nb_current_line = (it->i + it->offset) / it->ws_col;
}

static void	next_check(t_it *it)
{
	if (it->buffer == KL)
		move_left(it);
	else if (it->buffer == KR)
		move_right(it);
	if (!it->eof)
	{
		if (it->buffer == HOME && !it->r_video)
			move_begin(it);
		else if (it->buffer == END && !it->r_video)
			move_end(it);
		else if (it->buffer == ALT_LEFT)
			move_one_word_left(it);
		else if (it->buffer == ALT_RIGHT)
			move_one_word_right(it);
		else if (!it->r_video && ((it->buffer == ALT_UP) ||
		(it->buffer == ALT_DOWN)))
			move_up_and_down(it);
	}
}

static int	no_reverse_video(t_it *it)
{
	if (it->buffer == KU || it->buffer == KD || it->buffer == RET)
		print_history(it);
	else if (it->buffer == CTRL_U && it->line)
		cut_line(it);
	else if (it->buffer == CTRL_T && it->line)
		copy_tmpline(it);
	else if (it->buffer == CTRL_P)
		paste_line(it);
	else if (it->buffer == CTRL_L)
	{
		tputs(tgetstr(CLEAR_TERM, NULL), 0, my_putchar);
		print_prompt();
		if (it->line)
			ft_putstr(it->line);
	}
	else if (!it->line)
	{
		if (it->buffer == CTRL_D)
		{
			ft_putchar('\n');
			ft_exit(NULL, NULL);
		}
		return (1);
	}
	return (0);
}

void		edit_line(t_it *it)
{
	if (it->buffer == CTRL_R && it->line && it->i != it->len && !it->eof)
		put_reverse(it);
	if (!it->r_video)
	{
		if (!it->eof)
		{
			if (no_reverse_video(it))
				return ;
		}
		if (it->buffer == CTRL_D && it->i >= 0)
			del_current(it);
		else if (it->buffer == DEL && it->i > 0)
			del_char(it);
	}
	else if (it->r_video)
	{
		if (it->buffer == RET)
			put_reverse(it);
		if (it->buffer == U_CUT)
			ft_cut_select(it);
	}
	next_check(it);
}
