/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_terminal_data.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 10:48:26 by mfamilar          #+#    #+#             */
/*   Updated: 2016/04/28 11:14:15 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		handle_success(int success)
{
	if (success <= 0)
	{
		not_access();
		return (1);
	}
	return (0);
}

static int		modifiy_term(t_tty *tty)
{
	tty->term.c_lflag &= ~(ICANON);
	tty->term.c_lflag &= ~(ECHO);
	tty->term.c_cc[VMIN] = 1;
	tty->term.c_cc[VTIME] = 0;
	if (tcsetattr(0, TCSANOW, &tty->term) == -1)
	{
		tcsetattr_error();
		return (1);
	}
	return (0);
}

static int		init_termios_struct(t_tty *tty)
{
	if (tcgetattr(0, &tty->term) == -1)
	{
		tcgetattr_error();
		return (1);
	}
	if (modifiy_term(tty))
		return (1);
	return (0);
}

int				init_terminal_data(t_tty *tty)
{
	char			*name_term;
	int				success;

	name_term = NULL;
	if (!(name_term = getenv("TERM")))
		name_term = ft_strdup(TERM_ENV);
	success = tgetent(NULL, name_term);
	if (handle_success(success))
		return (1);
	if (init_termios_struct(tty))
		return (1);
	return (0);
}
