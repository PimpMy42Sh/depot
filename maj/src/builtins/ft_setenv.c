/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_setenv.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 11:50:06 by fjacquem          #+#    #+#             */
/*   Updated: 2016/09/22 11:50:09 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int			ft_check_equal(char *av)
{
	int		i;

	i = 0;
	while (av[i])
	{
		if (av[i] == '=')
			return (1);
		i++;
	}
	return (0);
}

static void			ft_setenv_suite(char **av, t_env *env)
{
	int		i;

	i = return_env_indice(env->environ, av[1]);
	if (i >= 0)
		replace_item_environ(env->environ, av[1], av[2]);
	else
		append_item_environ(env, av[1], av[2]);
}

int					ft_setenv(char **av, t_env *env)
{
	int		i;

	i = return_env_size(av);
	if (i == 1)
	{
		print_env(env->environ);
		return (1);
	}
	else if (i >= 4)
	{
		setenv_error(1);
		return (1);
	}
	else if (ft_check_equal(av[1]))
	{
		setenv_error(0);
		return (1);
	}
	ft_setenv_suite(av, env);
	return (1);
}
