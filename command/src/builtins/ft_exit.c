/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/25 11:18:11 by mfamilar          #+#    #+#             */
/*   Updated: 2016/08/23 17:05:47 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	exit_no_args(t_env *env)
{
	if (env)
	{
		free_double_array(env->environ);
		ft_memdel((void**)&env);
	}
	reset_term();
	exit(0);
}

static void	exit_with_args(char **av, t_env *env)
{
	int i;

	i = ft_atoi(av[1]);
	free_double_array(av);
	if (env)
	{
		free_double_array(env->environ);
		ft_memdel((void**)&env);
	}
	reset_term();
	exit(i);
}

static void	exit_failure(void)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("exit: Expression Syntax.\n", 2);
	ft_putstr_fd(RESET, 2);
}

void		ft_exit(char **av, t_env *env)
{
	if (!av || !av[1])
		exit_no_args(env);
	else if (av[1] && !ft_isalpha(av[1][0]) && !av[2])
		exit_with_args(av, env);
	else if (av[2] || ft_isalpha(av[1][0]))
		exit_failure();
}
