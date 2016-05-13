/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_environ_3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Marco <Marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 12:00:50 by mfamilar          #+#    #+#             */
/*   Updated: 2016/04/28 19:43:04 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			replace_item_environ(char **environ, char *env, char *av)
{
	int		i;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], env, ft_strlen(env))
			&& environ[i][ft_strlen(env)] == '=')
		{
			environ[i] = ft_strjoin(env, "=");
			if (av)
				environ[i] = ft_strjoin(environ[i], av);
		}
		i++;
	}
}

void			append_item_environ(char **environ, char *env, char *av)
{
	int		i;

	i = 0;
	while (environ[i])
		i++;
	environ[i] = ft_strjoin(env, "=");
	if (av)
		environ[i] = ft_strjoin(environ[i], av);
	i++;
	environ[i] = ft_memalloc(sizeof(char) * 2);
	environ[i] = 0;
}

void			loop_remove_env(char **av, char **environ)
{
	int			i;
	int			j;
	char		**env_var;

	i = 0;
	j = 0;
	while (av[i])
	{
		while (environ[j])
		{
			env_var = ft_strsplit(environ[j], '=');
			if (!ft_strncmp(env_var[0], av[i], ft_strlen(av[i])))
			{
				remove_env(environ, j);
				j--;
			}
			j++;
			free_double_array(env_var);
		}
		j = 0;
		i++;
	}
}

void			convert_tab(char *str)
{
	int		i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\t')
			str[i] = ' ';
		i++;
	}
}
