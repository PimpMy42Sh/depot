/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/24 09:32:39 by mfamilar          #+#    #+#             */
/*   Updated: 2016/04/25 14:55:42 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		print_prompt(void)
{
	char		*cwd;
	char		buffer[256];

	cwd = NULL;
	cwd = getcwd(buffer, 256);
	if (cwd)
	{
		ft_putstr(GREEN);
		ft_putstr("➜ ");
		ft_putstr(CYAN);
		ft_putstr(cwd);
		ft_putstr(RESET);
		ft_putstr(" ");
	}
	else
	{
		ft_putstr(GREEN);
		ft_putstr("$> ");
		ft_putstr(RESET);
	}
	rec_begin();
}
