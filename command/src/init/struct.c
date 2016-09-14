/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 15:26:03 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/14 11:46:46 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		init_struct(t_norme *norme)
{
	norme->i = 0;
	norme->u = 0;
	norme->current = 0;
	norme->previous = 0;
	norme->old = NULL;
	norme->pwd = NULL;
	norme->str = NULL;
	norme->copy = NULL;
	norme->boolean = 0;
}

t_tty		*ft_stock_term(t_tty *tty)
{
	static t_tty	*tmp = NULL;

	if (tty)
		tmp = tty;
	return (tmp);
}

static void		rec_tmp_size(t_it *it)
{
	struct winsize		win;
	
	ioctl(0, TIOCGWINSZ, &win);
	it->ws_col = win.ws_col;
}

t_it		*init_it_struct(int tmp)
{
	t_it			*it;

	it = (t_it*)ft_memalloc(sizeof(struct s_it));
	it->i = 0;
	it->len = 0;
	it->first = 0;
	it->offset = 0;
	it->buffer = 0;
	it->r_video = 0;
	it->nb_current_line = 0;
	it->tmp_buffer = NULL;
	it->tmp_line = NULL;
	it->line = NULL;
	it->eof = 0;
	it->ctrl_c = 0;
	if (!tmp)
		rec_size(it);
	else
		rec_tmp_size(it);
	return (it);
}

t_it		*ft_stock_it(t_it *it)
{
	static t_it	*tmp = NULL;

	if (it)
		tmp = it;
	return (tmp);
}
