/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 12:42:09 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/17 16:34:48 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void				ctrl_c(void)
{
	t_it		*it;

	it = ft_stock_it(NULL);
	tputs(tgetstr("me", NULL), 0, my_putchar);
	if (it)
	{
		ft_memdel((void**)&it->line);
		it->line = NULL;
		it->i = 0;
		it->r_video = 0;
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
