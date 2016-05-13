/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:40:39 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/10 15:44:36 by mfamilar         ###   ########.fr       */
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
