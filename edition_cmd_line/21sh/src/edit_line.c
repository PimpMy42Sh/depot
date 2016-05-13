/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 11:10:43 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/13 16:58:16 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			return_offset(void)
{
	char		*cwd;
	char		buffer[256];
	int			offset;

	offset = 0;
	cwd = NULL;
	cwd = getcwd(buffer, 256);
	if (cwd)
		offset = ft_strlen(cwd);
	else
		offset = 3;
	return (offset);
}

char		*copy_end_line(int j, int i, char *line)
{
	int		k;
	char	*tmp;

	tmp = ft_memalloc(sizeof(char) * ft_strlen(line));
	k = 0;
	while (line[j])
	{
		if (j >= i)
		{
			tmp[k] = line[j];
			k++;
		}
		j++;
	}
	tmp[k] = 0;
	return (tmp);
}

void		replace_char(t_it *it, int i)
{
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	int		j;
	int		k;

	j = 0;
	k = 0;
	tmp = ft_strdup(it->line);
	tmp3 = NULL;
	tmp[i] = it->buffer;
	tmp[i + 1] = 0;
	tmp3 = copy_end_line(j, i, it->line);
	tmp2 = ft_strjoin(tmp, tmp3);
	ft_memdel((void**)&it->line);
	it->line = ft_strdup(tmp2);
	tputs(tgetstr("im", NULL), 0, my_putchar);
	tputs(tgetstr("ic", NULL), 0, my_putchar);
	ft_putchar(it->buffer);
	tputs(tgetstr("ip", NULL), 0, my_putchar);
	tputs(tgetstr("ei", NULL), 0, my_putchar);
	free_elements(tmp, tmp2, tmp3, NULL);
}

static void	check_move(t_it *it, int offset)
{
	if (it->buffer == KL)
		move_left(it, offset);
	else if (it->buffer == KR)
		move_right(it, offset);
	else if (it->buffer == HOME && !it->r_video)
		move_begin(it, offset);
	else if (it->buffer == END && !it->r_video)
		move_end(it, offset);
	else if (it->buffer == ALT_LEFT)
		move_one_word_left(it, offset);
	else if (it->buffer == ALT_RIGHT)
		move_one_word_right(it, offset);
}

void		edit_line(t_it *it)
{
	int				offset;

	offset = return_offset() + 2;
	if (it->buffer == CTRL_R)
		put_reverse(it);
	if (!it->r_video)
	{
		if (it->buffer == KU || it->buffer == KD || it->buffer == RET)
			print_history(offset, it);
		if (it->buffer == CTRL_U && it->line)
			cut_line(it, offset);
		if (it->buffer == CTRL_P)
			paste_line(it, offset);
		if (!it->line)
		{
			if (it->buffer == CTRL_D)
			{
				ft_putchar('\n');
				exit(0);
			}
			return ;
		}
		if (it->buffer == CTRL_D && it->i > (offset - 1))
			del_current(it, offset);
		else if (it->buffer == DEL && it->i > offset)
			del_char(it, offset);
	}
	else if(it->r_video)
	{
		if (it->buffer == U_cut)
			ft_cut_select(it, 1);
		if (it->buffer == DEL)
			ft_cut_select(it, 0);
	}		
	check_move(it, offset);
}
