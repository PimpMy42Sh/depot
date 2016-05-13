/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/06 13:30:12 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/13 18:14:50 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_history			*go_to_end(t_history *history)
{
	t_history		*last_elem;

	last_elem = history;
	while (last_elem->next)
		last_elem = last_elem->next;
	return (last_elem);
}

static void			handle_history(int i, t_it *it)
{
	while (i--)
		move_left(it);
	tputs(tgetstr("ce", NULL), 0, my_putchar);
	tputs(tgetstr("cd", NULL), 0, my_putchar);
	ft_putstr(it->line);
	i = ft_strlen(it->line);
	while (i--)
		it->i++;
}

t_history			*up_history(t_history *list, t_it *it)
{
	int				i;

	i = 0;
	if (it->line)
		i = ft_strlen(it->line);
	if (!list->prev && !it->first)
		return (list);
	else if (list->prev && !it->first)
		it->line = ft_strdup(list->prev->cmd);
	else if (it->first)
		it->line = ft_strdup(list->cmd);
	handle_history(i, it);
	if (list->prev && !it->first)
		return (list->prev);
	else if (it->first)
		it->first = 0;
	return (list);
}

static t_history	*return_last_elem(t_it *it, t_history *list)
{
	int			i;

	i = 0;
	if (it->tmp_line)
	{
		it->line = ft_strdup(it->tmp_line);
		ft_putstr(it->line);
		i = ft_strlen(it->line);
		while (i--)
			it->i++;
	}
	else
		it->line = NULL;
	it->first = 1;
	return (list);
}

t_history			*down_history(t_history *list,
					t_it *it)
{
	int		i;

	i = 0;
	if (it->line)
		i = ft_strlen(it->line);
	while (i--)
		move_left(it);
	tputs(tgetstr("ce", NULL), 0, my_putchar);
	tputs(tgetstr("cd", NULL), 0, my_putchar);
	if (list->next)
	{
		list = list->next;
		it->line = ft_strdup(list->cmd);
		ft_putstr(list->cmd);
		i = ft_strlen(it->line);
		while (i--)
			it->i++;
		return (list);
	}
	else
		return (return_last_elem(it, list));
}
