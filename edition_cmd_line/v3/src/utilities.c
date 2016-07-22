/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:40:39 by mfamilar          #+#    #+#             */
/*   Updated: 2016/07/21 17:18:22 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int			my_putchar(int c)
{
	return (write(1, &c, 1));
}

void		check_only_space(t_it *it)
{
	int			i;

	if (!it->line)
		return ;
	i = 0;
	while (it->line[i])
	{
		if (it->line[i] != 32 && it->line[i] != '\n')
			return ;
		i++;
	}
	it->line = NULL;
}

void		go_to_bottom(t_it *it)
{
	int		nb_lines;

	nb_lines = 0;
	if (it->line)
	{
		nb_lines = (it->len + it->offset) / it->ws_col;
		if (nb_lines < 0)
			nb_lines = 0;
		tputs(tparm(tgetstr("DOWN_MAJ", NULL), nb_lines - 1), 0, my_putchar);
	}
}

int			ft_abs(int i)
{
	if (i >= 0)
		return (i);
	else
		return (-i);
}
