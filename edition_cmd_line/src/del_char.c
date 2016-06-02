/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 15:53:36 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/18 15:30:09 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int			copy_begin(int del, char *begin, t_it *it)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (i < del)
	{
		(begin)[j] = it->line[i];
		i++;
		j++;
	}
	i++;
	(begin)[j] = '\0';
	return (i);
}

static void			copy_end(int i, char *end, t_it *it)
{
	int		j;

	j = 0;
	while (it->line[i])
	{
		end[j] = it->line[i];
		i++;
		j++;
	}
}

void			del_char(t_it *it)
{
	int temp;

	if ((it->i) % it->ws_col == (it->ws_col - 2))
		move_right(it);
	del_char_buffer(it, 1);
	ft_memdel((void**)&it->tmp_line);
	it->tmp_line = ft_strdup(it->line);
	move_left(it);
	//tputs(tgetstr("dc", NULL), 0, my_putchar);
	multi_line_text(it);
}

void			del_current(t_it *it)
{
	if (!it->line[0])
	{
		ft_putchar('\n');
		exit(0);
	}
	//tputs(tgetstr("dc", NULL), 0, my_putchar);
	del_char_buffer(it, 0);
	multi_line_text(it);
	if (((ft_strlen(it->line) + it->offset) % it->ws_col == (it->ws_col - 1)))
		move_right(it);
}
