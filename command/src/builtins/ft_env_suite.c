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

static void			split_cmd(t_it *it, t_env *env, char *s)
{
	t_list				*c;

	nhdoc(0);
	alloc_size(ft_strlen(s));
	while (*s)
	{
		while ((c = get_pipeline(&s, env)))
		{
			if (it->line)
				execution(c, env);
			stop_cmd(c);
			s += (*s == ';');
		}
		s += (*s == ';');
	}
}

char				*env_parsing(char ***av)
{
	char		**tmp;
	char		*s;
	int			size;

	(*av)++;
	tmp = *av;
	size = 0;
	while (**av &&
		ft_strcmp(**av, "-i") &&
		ft_strcmp(**av, "-u"))
	{
		size += ft_strlen(**av) + 1;
		(*av)++;
	}
	s = ft_strnew(size);
	while (*tmp &&
		ft_strcmp(*tmp, "-i") &&
		ft_strcmp(*tmp, "-u"))
	{
		ft_strcat(s, *tmp);
		ft_strcat(s, " ");
		tmp++;
	}
	return (s);
}

static char			**void_env(void)
{
	char		**copy;

	copy = ft_memalloc(sizeof(char*));
	*copy = 0;
	return (copy);
}

void				env_parse(char *s)
{
	t_it	*it;
	t_env	e;

	e.environ = void_env();
	it = ft_stock_it(0);
	if (do_all_hdoc(s, e.environ))
		return ;
	split_cmd(it, &e, s);
	ft_memdel((void**)&e.environ);
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
