/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_suite.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/30 15:59:14 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/21 18:53:59 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include <command.h>

char				**void_env(void)
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

int					env_bad_arg(char *av)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("env: Bad option: ", 2);
	ft_putstr_fd(av, 2);
	ft_putstr_fd(RESET, 2);
	ft_putchar('\n');
	return (0);
}
