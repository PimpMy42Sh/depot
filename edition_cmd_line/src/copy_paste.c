/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 15:08:25 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/13 18:16:13 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		cut_line(t_it *it)
{
	int			i;

	i = 0;
	ft_memdel((void**)&it->tmp_buffer);
	it->tmp_buffer = ft_strdup(it->line);
	while (i < ft_strlen(it->line))
	{
		move_left(it);
		i++;
	}
	tputs(tgetstr("cd", NULL), 0, my_putchar);
	it->line = NULL;
}

static void	replace_it(t_it *it, char *tmp2)
{
	int		i;

	i = 0;
	while (tmp2[i++])
		it->i--;
	i = 0;
	while (it->tmp_buffer[i++])
		it->i--;
}

static void	paste_existing_line(t_it *it)
{
	int			i;
	int			j;
	char		*tmp;
	char		*tmp2;
	char		*tmp3;

	i = ((it->i - it->offset));
	j = 0;
	tmp = ft_memalloc(sizeof(char) * ft_strlen(it->line) +
		ft_strlen(it->tmp_buffer) + 1);
	ft_strncpy(tmp, it->line, i);
	while (tmp[j++])
		move_left(it);
	tmp2 = ft_strsub(it->line, i, ft_strlen(it->line));
	tmp3 = ft_strjoin(tmp, it->tmp_buffer);
	ft_memdel((void**)&it->line);
	it->line = ft_strjoin(tmp3, tmp2);
	replace_it(it, tmp2);
	free_elements(tmp, tmp2, tmp3, NULL);
}

static void	recalculate_it(t_it *it)
{
	int			i;

	i = 0;
	while (it->line[i])
	{
		it->i++;
		i++;
	}
}

void		paste_line(t_it *it)
{
	int		i;

	i = 0;
	if (!it->tmp_buffer)
		return ;
	else if (!it->line)
	{
		it->line = ft_strdup(it->tmp_buffer);
		ft_putstr(it->line);
	}
	else
	{
		tputs(tgetstr("sc", NULL), 0, my_putchar);
		paste_existing_line(it);
		ft_putstr(it->line);
		tputs(tgetstr("rc", NULL), 0, my_putchar);
		i = 0;
		while (it->tmp_buffer[i++])
		{
			it->i++;
			tputs(tgetstr("nd", NULL), 0, my_putchar);
		}
	}
	recalculate_it(it);
}
