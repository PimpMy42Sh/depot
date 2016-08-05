/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 12:42:09 by mfamilar          #+#    #+#             */
/*   Updated: 2016/08/05 17:51:45 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void				ctrl_c(void)
{
	t_it		*it;

	it = ft_stock_it(NULL);
	tputs(tgetstr(DEFAULT, NULL), 0, my_putchar);
	if (it)
	{
		it->eof = 0;
		it->r_video = 0;
		go_to_bottom(it);
		ft_memdel((void**)&it->line);
		it->i = 0;
		it->line = NULL;
		it->first = 1;
		ft_stock_it(it);
	}
	if (g_father == 0)
	{
		ft_putchar('\n');
		print_prompt();
	}
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
