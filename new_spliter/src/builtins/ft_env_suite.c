/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_suite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 15:59:14 by mfamilar          #+#    #+#             */
/*   Updated: 2016/07/22 10:51:27 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void			copy_environ(char **av, char **environ, t_norme *flags)
{
	int		i;
	int		j;

	i = return_env_size(environ);
	j = return_env_size(av);
	flags->copy = ft_memalloc(sizeof(char*) * (i + j + 1));
	i = 0;
	while (environ[i])
	{
		flags->copy[i] = ft_strdup(environ[i]);
		i++;
	}
	flags->copy[i] = 0;
}

static void		remove_variables(char **av)
{
	int		i;
	int		bol;

	i = 0;
	bol = 0;
	while (av[i])
	{
		if (av[i][0] != '=' && ft_strchr(av[i] + 1, '='))
		{
			remove_env(av, i);
			bol = 1;
		}
		if (bol == 0)
			i++;
		else
		{
			bol = 0;
			i = 0;
		}
	}
}

static void 		env_loop(char **av, t_norme *flags, int j)
{
	char	*tmp;
	char	*tmp2;
	int 	i;

	i = 0;
	tmp2 = NULL;
	tmp = NULL;
	while (av[i])
	{
		debug("LOOP", i);
		if (av[i][0] != '=' && ft_strchr(av[i] + 1, '='))
		{
			tmp = return_variable(av[i]);
			if ((tmp2 = return_env(flags->copy, tmp)))
			{
				replace_item(flags, tmp, av, i);
				ft_memdel((void**)&tmp2);
			}
			else
				flags->copy[j++] = ft_strdup(av[i]);
			ft_memdel((void**)&tmp);
		}
		i++;
	}
}

void			check_variables(t_norme *flags, char **av,
			char **environ)
{
	int		j;

	if (!flags->copy)
	{
		flags->copy = ft_memalloc(sizeof(char*) * (return_env_size(av) +
					(return_env_size(environ))));
		j = 0;
	}
	else
		j = return_env_size(flags->copy);
	env_loop(av, flags, j);
	flags->copy[j] = 0;
	remove_variables(av);
}

void			remove_flags(char **av, t_norme *flags)
{
	int		i;

	i = 0;
	remove_env(av, 0);
	while (av[i])
	{
		if (!ft_strcmp(av[i], "-i"))
		{
			flags->i = 1;
			remove_env(av, i);
			i--;
		}
		else if (!ft_strcmp(av[i], "-u"))
		{
			flags->u = 1;
			remove_env(av, i);
			i--;
		}
		else if (!ft_strcmp(av[i], "env"))
		{
			remove_env(av, i);
			i--;
		}
		i++;
	}
}
