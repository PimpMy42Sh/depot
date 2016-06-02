/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:18:11 by mfamilar          #+#    #+#             */
/*   Updated: 2016/04/28 11:48:34 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_exit(char **av, t_env *env)
{
	int		i;

	if (!av[1])
	{
		ft_putchar('\n');
		free_double_array(env->environ);
		ft_memdel((void**)&env);
		exit(0);
	}
	else if (av[1] && !ft_isalpha(av[1][0]) && !av[2])
	{
		i = ft_atoi(av[1]);
		free_double_array(av);
		ft_putchar('\n');
		free_double_array(env->environ);
		ft_memdel((void**)&env);
		exit(i);
	}
	else if (av[2] || ft_isalpha(av[1][0]))
	{
		ft_putstr_fd(RED, 2);
		ft_putchar('\n');
		ft_putstr_fd("exit: Expression Syntax.\n", 2);
		ft_putstr_fd(RESET, 2);
	}
}
