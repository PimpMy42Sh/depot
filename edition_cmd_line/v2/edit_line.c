/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_line.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/26 11:10:43 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/18 16:47:23 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	place_neg_cursor(t_it *it, int cur)
{
	int delta;

	while (cur)
	{
		if ((-cur + 1 + it->offset) % it->ws_col)
		{
			tputs(tgetstr("up", NULL), 0, my_putchar);
			tputs(tgetstr("cr", NULL), 0, my_putchar);
		}
		tputs(tgetstr("le", NULL), 0, my_putchar);
		cur++;
	}
}

void		place_cursor(t_it *it, int cur)
{
	int		delta;

	if (cur < 0)
	{
		//place_neg_cursor(it, cur);
	}
	else
	{
		while (cur > 0)
		{
			if ((cur + 1 + it->offset) % it->ws_col)
			{
				printf("%d\n", cur);
				tputs(tparm(tgetstr("DO", NULL), 1), 0, my_putchar);
				tputs(tgetstr("cr", NULL), 0, my_putchar);
			}
			tputs(tgetstr("nd", NULL), 0, my_putchar);
			cur--;
		}
	}
}


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

void		ft_yolo(int i)
{
	tputs(tgetstr("sc", NULL), 0, my_putchar);
	tputs(tgetstr("ho", NULL), 0, my_putchar);
	tputs(tgetstr("ce", NULL), 0, my_putchar);
	printf("i = %d\n", i);
	tputs(tgetstr("ce", NULL), 0, my_putchar);
	tputs(tgetstr("rc", NULL), 0, my_putchar);
}

void		multi_line_text(t_it *it)
{
	int	start;

	place_cursor(it, -(it->i + it->offset));
	start = it->size - (it->i - it->offset);
	//move_begin(it);
	tputs(tgetstr("cd", NULL), 0, my_putchar);
	ft_putstr(it->line);
	place_cursor(it, it->i + it->offset);
	//move_right(it);
 	//move_n_char(it, KL, start);
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
	multi_line_text(it);
	free_elements(tmp, tmp2, tmp3, NULL);
}

static void	check_move(t_it *it)
{
	if (it->buffer == KL && it->i >= 0)
		move_left(it);
	else if (it->buffer == KR && it->i < it->size)
		move_right(it);
	/*else if (it->buffer == HOME && !it->r_video)
		move_begin(it);
	else if (it->buffer == END && !it->r_video)
		move_end(it);
	else if (it->buffer == ALT_LEFT)
		move_one_word_left(it);
	else if (it->buffer == ALT_RIGHT)
		move_one_word_right(it);
	else if (!it->r_video && ((it->buffer == ALT_UP) || (it->buffer == ALT_DOWN)))
		move_up_and_down(it);
	ft_yolo(it->i);*/

}

void		edit_line(t_it *it)
{
	it->offset = return_offset() + 2;
	/*if (it->buffer == CTRL_R && it->line)
		put_reverse(it);
	if (!it->r_video)
	{
		if (it->buffer == KU || it->buffer == KD || it->buffer == RET)
			print_history(it);
		if (it->buffer == CTRL_U && it->line)
			cut_line(it);
		if (it->buffer == CTRL_T && it->line)
			copy_tmpline(it);
		if (it->buffer == CTRL_P)
			paste_line(it);
		if (it->buffer == CTRL_L)
		{
			tputs(tgetstr("cl", NULL), 0, my_putchar);
			print_prompt();
			if (it->line)
				ft_putstr(it->line);
		}
		if (!it->line)
		{
			if (it->buffer == CTRL_D)
			{
				ft_putchar('\n');
				exit(0);
			}
			return ;
		}
		if (it->buffer == CTRL_D && it->i > (it->offset - 1))
			del_current(it);
		else if (it->buffer == DEL && it->i > it->offset)
			del_char(it);
	}
	else if(it->r_video)
	{
		if (it->buffer == RET)
			put_reverse(it);
		if (it->buffer == U_cut)
			ft_cut_select(it);
	}*/
	check_move(it);
}
