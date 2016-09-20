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

static void		transform_line(char **av, t_norme *flags)
{
	int		i;
	char	*tmp;
	char	*buffer;

	i = 1;
	tmp = NULL;
	buffer = ft_memalloc(sizeof(char) * return_av_size(av));
	if (av[0])
	{
		tmp = ft_strdup(av[0]);
		ft_strcat(buffer, tmp);
		ft_strcat(buffer, " ");
		ft_memdel((void**)&tmp);
	}
	while (av[i])
	{
		ft_strcat(buffer, av[i]);
		ft_strcat(buffer, " ");
		ft_memdel((void**)&tmp);
		i++;
	}
	flags->str = ft_strdup(buffer);
	ft_memdel((void**)&buffer);
}

static int		copy_environ_uflag(char **environ, t_norme *flags, char **av)
{
	int		i;

	copy_environ(av, environ, flags);
	i = return_env_indice(flags->copy, av[0]);
	if (i >= 0)
		remove_env(flags->copy, i);
	i = return_env_size(av);
	if (i == 1)
	{
		print_env(flags->copy);
		return (1);
	}
	else
		remove_env(av, 0);
	return (0);
}

static int		parse_av(char **av, t_norme *flags, char **environ)
{
	int		i;

	i = 0;
	remove_flags(av, flags);
	if (flags->u)
	{
		i = return_env_size(av);
		if (i > 0 && copy_environ_uflag(environ, flags, av))
			return (1);
	}
	else
	{
		if (!flags->i)
			copy_environ(av, environ, flags);
		check_variables(flags, av, environ);
		i = return_env_size(av);
		if (i == 0)
		{
			print_env(flags->copy);
			return (1);
		}
	}
	transform_line(av, flags);
	return (0);
}

static int		ft_env_suite(char **av, char **environ, t_norme *flags)
{
	int		status;

	if (parse_av(av, flags, environ))
		return (1);
	g_father = fork();
	if (g_father > 0)
	{
		wait(&status);
		g_father = 0;
	}
	else
		parse_arguments(flags->copy, flags->str);
	return (0);
}

int				ft_env(char **av, char **environ)
{
	t_norme	*flags;

	flags = ft_memalloc(sizeof(t_norme));
	init_struct(flags);
	if (!av[1])
		print_env(environ);
	else if (av[1] && !ft_strcmp(av[1], "-u") && !av[2])
		env_error();
	else if (av[1] && !ft_strcmp(av[1], "-i") && !av[2])
	{
		free_struct(flags);
		return (1);
	}
	else
	{
		if (ft_env_suite(av, environ, flags))
		{
			free_struct(flags);
			return (1);
		}
	}
	free_struct(flags);
	return (1);
}
