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
		env_error();
		return (0);
	}
	return (1);
}

static int		exec(int *ok, char ***av)
{
	char		*str_parse;

	*ok = 1;
	if (!*((*av) + 1))
	{
		env_error();
		return (0);
	}
	str_parse = env_parsing(av);
	env_parse(str_parse);
	free(str_parse);
	return (1);
}

static void		bad_argument(int *ok, char *av)
{
	*ok = 1;
	ft_putstr_fd(RED, 2);
	ft_putstr_fd(av, 2);
	write(2, ": ", 2);
	write(2, "Bad argument\n", 13);
	ft_putstr_fd(RESET, 2);
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
		{
			if (!exec(&ok, &av))
				break ;
		}
		else
		{
			bad_argument(&ok, *av);
			break ;
		}
		av += !!*av;
	}
	if (!ok)
		print_env(environ);
	return (0);
}
