/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 12:42:09 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/15 17:24:42 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void				ctrl_c(void)
{
	t_it		*it;
	t_ctrl_c	*ctrl_c;

	ctrl_c = ft_stock_ctrl_c(NULL);
	it = ft_stock_it(NULL);
	tputs(tgetstr(DEFAULT, NULL), 0, my_putchar);
	resumed_terminal();
	if (it)
	{
		it->eof = 0;
		it->r_video = 0;
		go_to_bottom(it);
		ft_memdel((void**)&it->line);
		it->i = 0;
		it->buffer = 0;
		it->first = 1;
		//ft_stock_it(it);
	}
	if (g_father != 0)
	{
		ft_putchar('\n');
		print_prompt();
	}
	ctrl_c->stdin = 1;
	ctrl_c->bol = 1;
}

static void				signal_handler(int signum)
{
	if (signum == SIGINT)
		ctrl_c();
	else if (signum == SIGWINCH)
		rec_size(NULL);
	else
		return ;
}

void					check_signal(void)
{
	int			i;

	i = 1;
	while (i < 32)
	{
		signal(i, &signal_handler);
		i++;
	}
}
