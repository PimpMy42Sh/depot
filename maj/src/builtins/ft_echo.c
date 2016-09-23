/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 11:49:06 by fjacquem          #+#    #+#             */
/*   Updated: 2016/09/22 11:49:08 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

static void			print_string(char **av, char **environ, int delta, int flag)
{
	int				i;
	int				ok;

	ok = 0;
	i = delta;
	while (av[i])
	{
		ft_putstr(av[i]);
		if (*av[i])
			ok = 1;
		if (ok && av[i + 1])
			ft_putchar(' ');
		i++;
	}
	if (!flag)
		ft_putchar('\n');
	(void)environ;
}

static int			check_flags(char **av, int *flag)
{
	int			i;

	i = 1;
	if (av[i] && ft_strcmp(av[i], "-n"))
		return (i);
	while (av[i])
	{
		if (av[i] && !ft_strcmp(av[i], "-n"))
		{
			remove_env(av, i);
			*flag = 1;
		}
		if (av[i] && ft_strcmp(av[i], "-n") &&
			(!ft_strcmp(av[i], "--") || av[i][0] != ' '))
			return (i);
		i++;
	}
	return (i);
}

void				ft_echo(char **av, char **environ)
{
	int		i;
	int		flag;

	flag = 0;
	i = 0;
	if (!av[1])
	{
		ft_putchar('\n');
		return ;
	}
	else
		i = check_flags(av, &flag);
	if (flag && !av[i])
		return ;
	else if (flag && av[i])
		print_string(av, environ, i, flag);
	else
		print_string(av, environ, 1, flag);
}
