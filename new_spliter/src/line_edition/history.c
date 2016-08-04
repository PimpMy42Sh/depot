/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 13:30:12 by mfamilar          #+#    #+#             */
/*   Updated: 2016/07/19 10:20:56 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_history			*go_to_end(t_history *history)
{
	t_history		*last_elem;

	last_elem = history;
	while (last_elem->next)
		last_elem = last_elem->next;
	return (last_elem);
}

static void			handle_history(t_it *it)
{
	move_begin(it);
	tputs(tgetstr(CLEAR, NULL), 0, my_putchar);
	it->len = ft_strlen(it->line);
	multi_line_text(it);
}

t_history			*up_history(t_history *list, t_it *it)
{
	if (!list->prev && !it->first)
		return (list);
	else if (list->prev && !it->first)
	{
		ft_memdel((void**)&it->line);
		it->line = ft_strdup(list->prev->cmd);
	}
	else if (it->first)
	{
		ft_memdel((void**)&it->line);
		it->line = ft_strdup(list->cmd);
	}
	handle_history(it);
	if (list->prev && !it->first)
		return (list->prev);
	else if (it->first)
		it->first = 0;
	return (list);
}

static t_history	*return_last_elem(t_it *it, t_history *list)
{
	if (it->tmp_line)
	{
		it->line = ft_strdup(it->tmp_line);
		it->len = ft_strlen(it->line);
		multi_line_text(it);
	}
	else
		it->line = NULL;
	it->first = 1;
	return (list);
}

t_history			*down_history(t_history *list,
					t_it *it)
{
	move_begin(it);
	tputs(tgetstr(CLEAR, NULL), 0, my_putchar);
	ft_memdel((void**)&it->line);
	if (list->next)
	{
		list = list->next;
		it->line = ft_strdup(list->cmd);
		it->len = ft_strlen(it->line);
		multi_line_text(it);
		return (list);
	}
	else
		return (return_last_elem(it, list));
}
