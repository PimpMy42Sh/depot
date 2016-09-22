/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 12:42:09 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/20 10:05:26 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void				ctrl_c_bis(t_it *it, t_ctrl_c *ctrl_c)
{
	t_tty		*tty;

	tty = ft_stock_term(NULL);
	if (it)
	{
		it->eof = 0;
		it->r_video = 0;
		ft_memdel((void**)&it->line);
		it->i = 0;
		it->buffer = 0;
		it->first = 1;
	}
	if (!ctrl_c->main_loop)
	{
		tty->term.c_cc[VMIN] = 0;
		tcsetattr(0, TCSANOW, &tty->term);
	}
	ctrl_c->main_loop = 1;
	ctrl_c->bol = 1;
}

static void				ctrl_c(void)
{
	t_it		*it;
	t_ctrl_c	*ctrl_c;

	ctrl_c = ft_stock_ctrl_c(NULL);
	it = ft_stock_it(NULL);
	resumed_terminal();
	if (g_father != 0)
	{
		if (it)
			go_to_bottom(it);
		if (ctrl_c->main_loop)
		{
			ft_putchar('\n');
			print_prompt();
		}
	}
	ctrl_c_bis(it, ctrl_c);
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
