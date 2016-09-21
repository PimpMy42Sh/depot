/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/22 14:49:45 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/21 18:48:07 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		command_not_find(char *arg)
{
	t_it		*it;

	it = ft_stock_it(NULL);
	go_to_bottom(it);
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": Command not found.\n", 2);
	ft_putstr_fd(RESET, 2);
	ft_memdel((void**)&it);
	exit(1);
}

void		env_error(void)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("env: option requires an argument -- u\n", 2);
	ft_putstr_fd("usage: env [-iv] [-P utilpath] [-S string] [-u name]\n", 2);
	ft_putstr_fd("\t   [name=value ...] [utility [argument ...]]\n", 2);
	ft_putstr_fd(RESET, 2);
}

void		tcgetattr_error(void)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("tcgetattr failed. Abort.\n", 2);
	ft_putstr_fd(RESET, 2);
}

void		tcsetattr_error(void)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("tcsetattr failed. Abort.\n", 2);
	ft_putstr_fd(RESET, 2);
}
