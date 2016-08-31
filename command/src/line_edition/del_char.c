/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_char.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/09 15:53:36 by mfamilar          #+#    #+#             */
/*   Updated: 2016/08/05 17:07:54 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/*
** Fonction qui gère l'affichage du curseur lorsque l'on supprime du text
** en remontant une ligne
*/

static void	check_delete_first_elem(t_it *it, int old_size)
{
	int size;

	size = it->len + it->offset;
	if (it->i == it->len)
	{
		if ((size % it->ws_col) == it->ws_col - 1)
			tputs(tgetstr(DOWN, NULL), 0, my_putchar);
	}
	else if ((old_size % it->ws_col) == 0)
		tputs(tparm(tgetstr(DOWN_MAJ, NULL), 1), 0, my_putchar);
}

void		del_char(t_it *it)
{
	int size;

	size = it->len + it->offset;
	del_char_buffer(it, 1);
	it->len--;
	ft_memdel((void**)&it->tmp_line);
	it->tmp_line = ft_strdup(it->line);
	move_left(it);
	multi_line_text(it);
	check_delete_first_elem(it, size);
}

void		del_current(t_it *it)
{
	int size;

	size = it->len + it->offset;
	if (it->eof && !it->len)
		return ;
	if (!it->line[0])
		ft_exit(NULL, NULL);
	del_char_buffer(it, 0);
	if (it->i != it->len)
		it->len--;
	multi_line_text(it);
	check_delete_first_elem(it, size);
}
