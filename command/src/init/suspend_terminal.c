/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   suspend_terminal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/28 10:04:14 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/15 17:34:38 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		suspend_terminal(void)
{
	t_tty	*tty;

	tty = NULL;
	tty = ft_stock_term(NULL);
	tcsetattr(0, TCSANOW, &tty->backup);
	ft_stock_term(tty);
}

void		resumed_terminal(void)
{
	t_tty	*tty;

	tty = NULL;
	tty = ft_stock_term(NULL);
	tcsetattr(0, TCSANOW, &tty->term);
	ft_stock_term(tty);
}
