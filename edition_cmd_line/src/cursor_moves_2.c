/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cursor_moves_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/03 15:27:27 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/18 14:11:10 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void				move_end(t_it *it)
{
	int	last_i;

	last_i = 0;
	it->buffer = ALT_DOWN;
	while (it->i != last_i)
	{
		last_i = it->i;
		move_up_and_down(it);
	}
}

static void			init_tmp(char **tmp, char **tmp2, char *line)
{
	*tmp2 = ft_memalloc(sizeof(char) * ft_strlen(line));
	*tmp = ft_memalloc(sizeof(char) * ft_strlen(line));
}

static void			copy_line(int i, char *tmp, char *line)
{
	int		j;

	j = 0;
	while (j < i)
	{
		tmp[j] = line[j];
		j++;
	}
	tmp[j] = '\0';
}

void				del_char_buffer(t_it *it, int current)
{
	char	*tmp;
	char	*tmp2;
	int		i;
	int		j;
	int 	temp;

	init_tmp(&tmp, &tmp2, it->line);
	i = (it->i - it->offset) - current;
	copy_line(i, tmp, it->line);
	j = 0;
	i++;
	temp = ft_strlen(it->line);
	while (it->line[i] && i < temp)
	{
		tmp2[j] = it->line[i];
		i++;
		j++;
	}
	tmp2[j] = '\0';
	ft_memdel((void**)&it->line);
	if (!tmp)
		return ;
	it->line = ft_strjoin(tmp, tmp2);
	free_elements(tmp, tmp2, NULL, NULL);
}

void			move_up_and_down(t_it *it)
{
	int 	i;
	int		fd;

	i = 0;
	if (it->buffer == ALT_UP)
	{
		if (it->i - (it->ws_col + 1) > it->offset)
		{
			tputs(tgetstr("up", NULL), 0, my_putchar);
			it->i -= it->ws_col;
		}
		else
			move_n_char(it, KL, it->ws_col);
	}
	else if (it->buffer == ALT_DOWN)
	{
		if (it->i + (it->ws_col + 1 ) < ft_strlen(it->line))
		{
			tputs(tparm(tgetstr("DO", NULL), 1), 0, my_putchar);
			it->i += it->ws_col;
		}
		else
			move_n_char(it, KR, it->ws_col);
	}
}
