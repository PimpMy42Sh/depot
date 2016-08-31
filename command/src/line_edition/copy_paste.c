/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_paste.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/11 15:08:25 by mfamilar          #+#    #+#             */
/*   Updated: 2016/07/19 12:46:22 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		copy_tmpline(t_it *it)
{
	ft_memdel((void**)&it->tmp_buffer);
	it->tmp_buffer = ft_strdup(it->line);
}

static void	paste_existing_line(t_it *it)
{
	char		*tmp;
	char		*tmp2;
	char		*tmp3;

	tmp = ft_memalloc(sizeof(char) * it->len + ft_strlen(it->tmp_buffer) + 1);
	ft_strncpy(tmp, it->line, it->i);
	tmp2 = ft_strsub(it->line, it->i, it->len);
	tmp3 = ft_strjoin(tmp, it->tmp_buffer);
	ft_memdel((void**)&it->line);
	it->line = ft_strjoin(tmp3, tmp2);
	it->len = ft_strlen(it->line);
	free_elements(tmp, tmp2, tmp3, NULL);
}

void		paste_line(t_it *it)
{
	if (!it->tmp_buffer)
		return ;
	else if (!it->line)
	{
		it->line = ft_strdup(it->tmp_buffer);
		it->len = ft_strlen(it->line);
	}
	else
		paste_existing_line(it);
	multi_line_text(it);
	move_n_char(it, KR, ft_strlen(it->tmp_buffer));
}
