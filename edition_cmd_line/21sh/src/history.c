/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 16:31:26 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/10 15:35:54 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history				*ft_stock_history(t_history *history)
{
	static t_history	*tmp = NULL;

	if (history)
		tmp = history;
	return (tmp);
}

static t_history		*create_first_elem(char *line, t_history *history)
{
	history = ft_memalloc(sizeof(t_history));
	history->cmd = ft_strdup(line);
	history->next = NULL;
	history->prev = NULL;
	return (history);
}

static t_history		*create_next_elem(char *line, t_history *history,
						t_history *prev)
{
	while (history)
	{
		prev = history;
		history = history->next;
	}
	history = ft_memalloc(sizeof(t_history));
	history->cmd = ft_strdup(line);
	history->next = NULL;
	history->prev = prev;
	prev->next = history;
	return (prev);
}

t_history				*create_elem(t_history *history, char *line)
{
	static t_history		*begin = NULL;
	t_history				*prev;

	prev = NULL;
	if (!history)
	{
		history = create_first_elem(line, history);
		begin = history;
	}
	else if (history)
		history = create_next_elem(line, history, prev);
	ft_stock_history(begin);
	return (begin);
}

void					print_history(int offset, t_it *it)
{
	t_history			*history;
	static t_history	*list = NULL;
	int					i;

	i = 0;
	history = ft_stock_history(NULL);
	if (!history)
		return ;
	if (!it->line)
		it->tmp_line = NULL;
	if (!list || it->buffer == RET)
	{
		list = go_to_end(history);
		if (it->buffer == RET)
			list = list->next;
		it->first = 1;
	}
	if (it->buffer == KU)
		list = up_history(list, it, offset);
	if (it->buffer == KD)
		list = down_history(list, it, offset);
}
