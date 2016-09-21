/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suspend_terminal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 10:04:14 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/21 19:07:17 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		suspend_terminal(void)
{
	t_tty	*tty;

	tty = ft_stock_term(NULL);
	tcsetattr(0, TCSANOW, &tty->backup);
}

void		resumed_terminal(void)
{
	t_tty	*tty;

	tty = ft_stock_term(NULL);
	tty->term.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &tty->term);
}
