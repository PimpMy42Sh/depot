/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/10 12:42:09 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/18 11:49:03 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void				ctrl_c(void)
{
	t_it		*it;
	t_history	*list;
	t_history	*history;
	int			nb_lines;

	nb_lines = 0;
	it = ft_stock_it(NULL);
	list = ft_stock_list(NULL);
	history = ft_stock_history(NULL);
	tputs(tgetstr("me", NULL), 0, my_putchar);
	if (it)
	{
		it->r_video = 0;
		go_to_bottom(it);
		ft_memdel((void**)&it->line);
		it->i = 0;
		it->line = NULL;
		ft_stock_it(it);
	}
	if (list)
	{
		list = go_to_end(history);
		printf("list = %s\n", list->cmd);
		list = list->next;
		//printf("list = %s\n", list->cmd);
		it->first = 1;
		ft_stock_it(it);
		ft_stock_list(list);
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
