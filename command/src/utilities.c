/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:40:39 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/21 17:33:10 by Marco            ###   ########.fr       */
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
	ft_memdel((void**)&it->line);
}

void		go_to_bottom(t_it *it)
{
	move_end(it);
	tputs(tgetstr(BEGIN, NULL), 0, my_putchar);
}

int			ft_abs(int i)
{
	if (i >= 0)
		return (i);
	else
		return (-i);
}
