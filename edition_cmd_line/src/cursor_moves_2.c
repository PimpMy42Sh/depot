/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_moves_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:27:27 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/13 18:09:49 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				move_end(t_it *it)
{
	while (it->i < it->offset + ft_strlen(it->line))
	{
		it->i++;
		tputs(tgetstr("nd", NULL), 0, my_putchar);
	}
}

static void			init_tmp(char **tmp, char **tmp2, int *j, char *line)
{
	*j = 0;
	*tmp2 = ft_memalloc(sizeof(char) * ft_strlen(line));
	*tmp = ft_memalloc(sizeof(char) * ft_strlen(line));
}

static void			copy_line(int i, int j, char *tmp, char *line)
{
	while (j < i)
	{
		tmp[j] = line[j];
		j++;
	}
}

void				del_char_buffer(t_it *it)
{
	char	*tmp;
	char	*tmp2;
	int		i;
	int		j;

	init_tmp(&tmp, &tmp2, &j, it->line);
	i = (it->i - it->offset) - 1;
	copy_line(i, j, tmp, it->line);
	j = 0;
	i++;
	while (it->line[i])
	{
		tmp2[j] = it->line[i];
		i++;
		j++;
	}
	ft_memdel((void**)&it->line);
	if (!tmp)
		return ;
	it->line = ft_strjoin(tmp, tmp2);
	free_elements(tmp, tmp2, NULL, NULL);
}
