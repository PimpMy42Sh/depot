/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_text.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/13 10:37:19 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/14 15:05:11 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			ft_abs(int i)
{
	if (i >= 0)
		return(i);
	else
		return(-i);
}

void		ft_move_saved(t_it *it)
{
	int target;

	if (it->i > it->saved_i)
	{
		target = it->saved_i;
		while (it->i != target)
			move_left(it);
	}

}

char	*ft_strsub_rev(char const *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	i;
	int		k;

	str = ft_memalloc((ft_strlen(s) - len) + 1);
	i = 0;
	k = 0;
	if (str == NULL)
		return (NULL);
	while (s[i])
	{
		if (i < start || i > start + len)
		{
			str[k] = s[i];
			k++;
		}
		i++;
	}
	str[k] = '\0';
	return (str);
}

void		ft_cut_select(t_it *it, int save)
{
	int		length;
	int		temp;

	tputs(tgetstr("ve", NULL), 0, my_putchar);
	tputs(tgetstr("me", NULL), 0, my_putchar);
	length = ft_abs(it->i - it->saved_i);
	temp = it->i;
	move_begin(it);
	if (temp > it->saved_i)
	{
		if (save)
			it->tmp_buffer = ft_strsub(it->line, ((it->saved_i - return_offset() - 2)), length);
		it->line = ft_strsub_rev(it->line, ((it->saved_i - return_offset())), length + 1);
	}
	else
	{
		if (save)
			it->tmp_buffer = ft_strsub(it->line, ((temp - return_offset() - 2)), length);
		it->line = ft_strsub_rev(it->line, ((temp - return_offset())), length + 1);
	}
	ft_putstr(it->line);
	it->i += ft_strlen(it->line);
}

/*char		ft_yolo(t_it *it)
{
	char	*str;
	int		i;
	int		length;

	length = ft_abs(it->i - it->saved_i);
	str = ft_memalloc(length + 1 * sizeof(char));
	i = 0;
	if (it->i > it->saved)
	{
		while (i < length)
		{
			str[i] = it->line[(it->i - return_offset() - 2)]
		}
	}
	else
	{
		while (i < length)
	}
}*/

void		ft_replace_vid(t_it *it, int rewrite)
{
	int		length;
	int		temp;

	if (rewrite)
	{
		tputs(tgetstr("mr", NULL), 0, my_putchar);
		ft_putchar(it->line[(it->i - return_offset() - 2)]);
		tputs(tgetstr("le", NULL), 0, my_putchar);
	}
	else
	{
		temp = it->i;
		tputs(tgetstr("ve", NULL), 0, my_putchar);
		tputs(tgetstr("me", NULL), 0, my_putchar);
		length = ft_abs(it->i - it->saved_i);
		ft_move_saved(it);
		//it->tmp_buffer = ft_yolo(it);
		if (temp > it->saved_i)
			it->tmp_buffer = ft_strsub(it->line, ((it->i - return_offset() - 2)), length + 1);
		else
			it->tmp_buffer = ft_strsub(it->line, ((temp - return_offset() - 2)), length + 1);
		ft_putstr(it->tmp_buffer);
		it->i += ft_strlen(it->tmp_buffer);
	}
}

void		put_reverse(t_it *it)
{
	if (it->r_video == 0)
	{
		it->r_video = 1;
		it->saved_i = it->i;
		ft_replace_vid(it, 1);
	}
	else
	{
		it->r_video = 0;
		ft_replace_vid(it, 0);
	}
}