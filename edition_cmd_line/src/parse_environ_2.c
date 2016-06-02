/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_environ_2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/01 18:43:17 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/09 16:07:42 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			print_env(char **environ)
{
	int		i;

	i = 0;
	ft_putchar('\n');
	while (environ[i])
	{
		ft_putstr(environ[i]);
		ft_putchar('\n');
		i++;
	}
}

void			replace_item(t_norme *flags, char *env, char **av, int indice)
{
	int		i;

	i = 0;
	while (flags->copy[i])
	{
		if (!ft_strncmp(flags->copy[i], env, ft_strlen(env)))
		{
			//ft_memdel((void**)&flags->copy[i]);
			free(flags->copy[i]);
			flags->copy[i] = ft_strdup(av[indice]);
		}
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

char			*return_variable(char *str)
{
	char	*ret;
	int		i;

	i = 0;
	ret = ft_strdup(str);
	while (str[i] != '=')
	{
		ret[i] = str[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

void			map_environ(char **environ)
{
	int		i;

	i = 0;
	while (environ[i])
	{
		if (!ft_strcmp(environ[i], ""))
			environ[i] = 0;
		i++;
	}
}
