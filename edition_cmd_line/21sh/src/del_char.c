/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 15:53:36 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/11 14:29:59 by mfamilar         ###   ########.fr       */
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

void				del_current(t_it *it, int offset)
{
	int		i;
	int		del;
	char	*begin;
	char	*end;

	del = (it->i - offset);
	i = 0;
	begin = ft_memalloc(sizeof(char) * ft_strlen(it->line));
	end = ft_memalloc(sizeof(char) * ft_strlen(it->line));
	i = copy_begin(del, begin, it);
	copy_end(i, end, it);
	ft_memdel((void**)&it->line);
	it->line = ft_strjoin(begin, end);
	free_elements(begin, end, NULL, NULL);
	tputs(tgetstr("im", NULL), 0, my_putchar);
	tputs(tgetstr("dc", NULL), 0, my_putchar);
	tputs(tgetstr("ip", NULL), 0, my_putchar);
	tputs(tgetstr("ei", NULL), 0, my_putchar);
}
