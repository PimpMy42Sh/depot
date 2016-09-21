/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_suite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 15:59:14 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/13 16:21:14 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <command.h>

char			**void_env(void)
{
	char		**copy;

	copy = ft_memalloc(sizeof(char*));
	*copy = 0;
	return (copy);
}

void				env_parse(char **s, char **env)
{
	g_father = 0;
	if (!fork())
		start_prgm(env, s);
	wait(NULL);
	g_father = 1;
}

char				**copy_environ(char **environ)
{
	int				i;
	char			**copy;

	i = return_env_size(environ);
	copy = ft_memalloc(sizeof(char*) * (i + 1));
	i = 0;
	while (environ[i])
	{
		copy[i] = ft_strdup(environ[i]);
		i++;
	}
	copy[i] = 0;
	return (copy);
}
