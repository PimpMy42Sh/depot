/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:40:39 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/18 16:47:06 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			my_putchar(int c)
{
	return (write(2, &c, 1));
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
	//	ft_yolo(nb_lines, it);
		nb_lines = (ft_strlen(it->line) + it->offset) / it->ws_col - (it->i / it->ws_col);
		if (nb_lines < 0)
			nb_lines = 0;
		while (nb_lines--)
		{
			//tputs(tgetstr("do", NULL), 0, my_putchar);
			tputs(tgetstr("sf", NULL), 0, my_putchar);
		}
	}
}

int			ft_abs(int i)
{
	if (i >= 0)
		return(i);
	else
		return(-i);
}