/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_environ_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 18:43:17 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/21 19:23:19 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void			print_env(char **environ)
{
	int		i;

	i = 0;
	while (environ[i])
	{
		ft_putstr(environ[i]);
		ft_putchar('\n');
		i++;
	}
}

int				return_env_size(char **environ)
{
	int		i;

	i = 0;
	while (environ[i])
		i++;
	return (i);
}

void			replace_item_environ(char **environ, char *env, char *av)
{
	int		i;
	char	*tmp;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], env, ft_strlen(env))
			&& environ[i][ft_strlen(env)] == '=')
		{
			ft_memdel((void**)&environ[i]);
			environ[i] = ft_strjoin(env, "=");
			if (av)
			{
				tmp = ft_strdup(environ[i]);
				ft_memdel((void**)&environ[i]);
				environ[i] = ft_strjoin(tmp, av);
				ft_memdel((void**)&tmp);
			}
		}
		i++;
	}
}

void			append_item_environ(t_env *env, char *environ, char *av)
{
	int		i;
	char	**new_environ;
	char	*tmp;

	i = return_env_size(env->environ);
	new_environ = (char**)ft_memalloc(sizeof(char*) * (i + 2));
	i = 0;
	while (env->environ[i])
	{
		new_environ[i] = env->environ[i];
		i++;
	}
	new_environ[i] = ft_strjoin(environ, "=");
	if (av)
	{
		tmp = new_environ[i];
		new_environ[i] = ft_strjoin(tmp, av);
		ft_memdel((void**)&tmp);
	}
	i++;
	new_environ[i] = NULL;
	ft_memdel((void**)&env->environ);
	env->environ = new_environ;
}

void			loop_remove_env(char **av, t_env *env)
{
	int			i;
	int			j;
	char		**env_var;

	i = 0;
	j = 0;
	while (av[i])
	{
		while (env->environ[j])
		{
			env_var = ft_strsplit(env->environ[j], '=');
			if (!ft_strcmp(env_var[0], av[i]))
			{
				remove_env(env->environ, j);
				j--;
			}
			j++;
			free_double_array(env_var);
		}
		j = 0;
		i++;
	}
}
