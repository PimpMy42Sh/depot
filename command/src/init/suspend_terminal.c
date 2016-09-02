/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suspend_terminal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 10:04:14 by mfamilar          #+#    #+#             */
/*   Updated: 2016/07/11 14:38:53 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		suspend_terminal(void)
{
	t_tty	*tty;

	tty = NULL;
	tty = ft_stock_term(NULL);
	//tty->term.c_lflag |= (ICANON | ECHO);
	tcsetattr(0, TCSANOW, &tty->backup);
}

void		resumed_terminal(void)
{
	t_tty	*tty;

	tty = NULL;
	tty = ft_stock_term(NULL);
	tcsetattr(0, TCSANOW, &tty->term);
}
