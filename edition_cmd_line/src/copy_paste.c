/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 15:08:25 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/18 15:41:43 by mfamilar         ###   ########.fr       */
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
	tmp2 = ft_strsub(it->line, i, ft_strlen(it->line));
	tmp3 = ft_strjoin(tmp, it->tmp_buffer);
	//ft_yolo(tmp, tmp3);
	ft_memdel((void**)&it->line);
	it->line = ft_strjoin(tmp3, tmp2);
	free_elements(tmp, tmp2, tmp3, NULL);
	//ft_yolo(it->line, it->tmp_buffer);
}

void		paste_line(t_it *it)
{
	int temp;

	tputs(tgetstr("LP", NULL), 0, my_putchar);
	if (!it->tmp_buffer)
		return ;
	else if (!it->line)
		it->line = ft_strdup(it->tmp_buffer);
	else
		paste_existing_line(it);
	multi_line_text(it, 0);
	if (it->i - it->offset == ft_strlen(it->line))
		move_n_char(it, KR, ft_strlen(it->tmp_buffer) + 1);
	else
		move_n_char(it, KR, ft_strlen(it->tmp_buffer));
}
