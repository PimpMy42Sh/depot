/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 11:55:33 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/13 16:21:46 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <command.h>

static int		unset(int *ok, char ***av, char **env)
{
	if (*((*av) + 1))
	{
		(*av)++;
		remove_env(env, return_env_indice(env, **av));
	}
	else
	{
		*ok = 1;
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("env: Bad option: -u: ", 2);
		ft_putstr_fd("Need a variable name", 2);
		ft_putstr_fd(RESET, 2);
		ft_putchar('\n');
		return (0);
	}
	return (1);
}

char				**exec_tab_parser(char **av, int *type_exec)
{
	int				i;
	char			**tabl;

	i = 0;
	while (av[i] && ft_strchr(av[i], '='))
		i++;
	if ((*type_exec = !!av[i]))
		tabl = copy_environ(&av[i]);
	else
		tabl = copy_environ(av);
	return (tabl);
}

static int		exec(int *ok, char **av, char **env)
{
	char		**tabl;

	av += !env;
	if ((tabl = exec_tab_parser(av, ok)))
	{
		if (*ok)
			env_parse(tabl, env);
		else
		{
			if (env)
				print_env(env);
			print_env(tabl);
		}
		free_double_array(tabl);
	}
	return (1);
}

int				ft_env(char **av, char **environ, int ok)
{
	av++;
	while (*av)
	{
		if (!ft_strcmp("-u", *av))
		{
			if (!unset(&ok, &av, environ))
				break ;
		}
		else if (!ft_strcmp("-i", *av))
			return (exec(&ok, av, NULL));
		else if (**av != '-' || !ft_strcmp("--", *av))
		{
			av += (**av == '-');
			return (exec(&ok, av, environ));
		}
		else 
		{
			ft_putstr_fd(RED, 2);
			ft_putstr_fd("env: Bad option: ", 2);
			ft_putstr_fd(*av, 2);
			ft_putstr_fd(RESET, 2);
			ft_putchar('\n');
			return (0);
		}
		av += !!*av;
	}
	if (!ok)
		print_env(environ);
	return (0);
}
