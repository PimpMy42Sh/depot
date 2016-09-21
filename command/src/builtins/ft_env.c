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
	int			index;

	if (*((*av) + 1))
	{
		(*av)++;
		if ((index = return_env_indice(env, **av)) != -1)
			remove_env(env, index);
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
	printf("OUT\n");
	return (1);
}

char			**exec_tab_parser(char **av, int *type_exec)
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

static int		replace(char *av, char **env)
{
	char		*str;
	char		tmp;
	int			len;

	str = ft_strchr(av, '=') + 1;
	tmp = *str;
	*str = 0;
	len = ft_strlen(av);
	*str = tmp;
	while (*env)
	{
		if (!ft_strncmp(av, *env, len))
		{
			free(*env);
			*env = ft_strdup(av);
			*av = 0;
			return (1);
		}
		env++;
	}
	return (0);
}

static void		add_env(char *av, char ***env)
{
	int			i;
	char		**copy;

	i = return_env_size(*env) + 2;
	copy = (char**)malloc(sizeof(char*) * (i + 1));
	i = 0;
	while ((*env)[i])
	{
		copy[i] = ft_strdup((*env)[i]);
		free((*env)[i]);
		i++;
	}
	copy[i] = ft_strdup(av);
	copy[i + 1] = 0;
	free(*env);
	*env = copy;
}

static int		exec(int *ok, char **av, char ***env)
{
	char		**tabl;
	int			i;

	av += !env;
	if ((tabl = exec_tab_parser(av, ok)))
	{
		if (*ok)
			env_parse(tabl, env);
		else
		{
			i = 0;
			while (tabl[i])
			{
				if (!replace(tabl[i], *env))
					add_env(tabl[i], env);
				i++;
			}
			print_env(*env);
		}
		free_double_array(tabl);
	}
	return (1);
}

int				ft_env(char **av, char ***environ, int ok)
{
	av++;
	while (*av)
	{
		if (!ft_strcmp("-u", *av))
		{
			if (!unset(&ok, &av, *environ))
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
		print_env(*environ);
	return (0);
}
