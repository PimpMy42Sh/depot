/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 15:26:03 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/21 19:09:52 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	rec_tmp_size(t_it *it)
{
	struct winsize		win;

	ioctl(0, TIOCGWINSZ, &win);
	it->ws_col = win.ws_col;
}

t_it		*init_it_struct(int tmp)
{
	t_it			*it;

	it = (t_it*)ft_memalloc(sizeof(struct s_it));
	ft_bzero(it, sizeof(t_it));
	if (!tmp)
		rec_size(it);
	else
		rec_tmp_size(it);
	return (it);
}
