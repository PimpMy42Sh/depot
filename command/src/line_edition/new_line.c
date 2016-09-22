/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_line.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Marco <Marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/21 12:26:42 by Marco             #+#    #+#             */
/*   Updated: 2016/09/21 14:01:37 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/command.h"

static void		append_backlash_n(t_it *it, t_list **args)
{
	char	*tmp;

	tmp = ft_strjoin(it->line, "\n");
	ft_memdel((void**)&it->line);
	it->line = ft_strdup(tmp);
	ft_lstadd_end(args, ft_lstnew(it->line, ft_strlen(it->line) + 1));
	ft_memdel((void**)&tmp);
}

static int		browse_line(char **str, char *end, char other)
{
	while (**str)
	{
		if (**str == *end)
		{
			browse_skip_quote(str, *end);
			if (!**str)
				return (0);
		}
		if (**str == other)
		{
			browse_skip_quote(str, other);
			if (!**str)
			{
				*end = other;
				return (0);
			}
		}
		(*str)++;
	}
	return (1);
}

static int		close_or_not(char **str, char *end)
{
	char	other;

	if (*end == QUOTES)
		other = D_QUOTES;
	else
		other = QUOTES;
	while (**str != *end)
		(*str)++;
	(*str)++;
	if (!**str)
		return (1);
	return (browse_line(str, end, other));
}

static void		display_delta(t_it *it)
{
	int		delta;

	delta = (it->len + 2) / it->ws_col;
	move_begin(it);
	while (delta)
	{
		tputs(tgetstr(DOWN, NULL), 0, my_putchar);
		delta--;
	}
}

int				is_a_newline_quotes(t_it *it, char *end, t_list **args)
{
	char	*str;
	char	*begin;

	display_delta(it);
	if (!it->line)
		ft_lstadd_end(args, ft_lstnew("\n", 2));
	else
	{
		str = ft_strdup(it->line);
		begin = str;
		if (ft_strchr(it->line, *end) && close_or_not(&str, end))
		{
			ft_memdel((void**)&begin);
			ft_lstadd_end(args, ft_lstnew(it->line, ft_strlen(it->line) + 1));
			write(1, "\n", 1);
			return (0);
		}
		ft_memdel((void**)&begin);
		append_backlash_n(it, args);
	}
	return (1);
}
