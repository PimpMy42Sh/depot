/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors_2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 14:47:26 by mfamilar          #+#    #+#             */
/*   Updated: 2016/08/23 17:48:44 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		permission_denied(char *str, char *path)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": permission denied\n", 2);
	ft_putstr_fd(RESET, 2);
}

void		setenv_error(int boolean)
{
	ft_putstr_fd(RED, 2);
	if (boolean)
		ft_putstr_fd("setenv: Too many arguments.\n", 2);
	else
	{
		ft_putstr_fd("setenv: Variable name must contain ", 2);
		ft_putstr_fd("alphanumeric characters.\n", 2);
	}
	ft_putstr_fd(RESET, 2);
}

void		unsetenv_error(void)
{
	ft_putstr_fd(RED, 2);
	ft_putchar('\n');
	ft_putstr_fd("unsetenv: Too few arguments.\n", 2);
}

void		not_access(void)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("Could not access the termcap data base.\n", 2);
	ft_putstr_fd(RESET, 2);
}

void		cant_move_home(void)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("cd: Can't change to home directory.\n", 2);
	ft_putstr_fd(RESET, 2);
}
