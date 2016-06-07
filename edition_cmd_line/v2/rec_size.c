/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rec_size.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/17 11:00:59 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/17 11:42:42 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		rec_size(t_it *it)
{
	t_it 	*rec;
	struct winsize		win;

	ioctl(0, TIOCGWINSZ, &win);
	if (!it)
		rec = ft_stock_it(NULL);
	else
		rec = it;
	rec->ws_col = win.ws_col;
	ft_stock_it(rec);
}