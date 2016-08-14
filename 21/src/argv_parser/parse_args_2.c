/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 17:42:35 by mfamilar          #+#    #+#             */
/*   Updated: 2016/07/11 14:40:01 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
/*
int			check_line(char *line, t_env *env, int boolean)
{
	char	**av;

	if (!line)
		return (1);
	convert_tab(line);
	av = ft_strsplit(line, ' ');
	if (!av[0])
	{
		free_double_array(av);
		return (1);
	}
	check_tilde_and_dollar(env->environ, av, boolean);
	map_environ(env->environ);
	if (!(ft_strcmp(av[0], "cd")) || !(ft_strcmp(av[0], "setenv")) ||
			!(ft_strcmp(av[0], "unsetenv")) || !(ft_strcmp(av[0], "exit"))
			|| !ft_strcmp(av[0], "env"))
		return (check_builtins(av, env));
	free_double_array(av);
	return (0);
}
*/
static char	*replace_environ_suite(char **environ, char *search)
{
	int		j;
	char	*ret;

	j = 0;
	ret = NULL;
	while (environ[j] && !ft_strcmp(search, "HOME"))
	{
		if (!ft_strncmp(environ[j], search, 4))
			ret = ft_strsub(environ[j], 5, ft_strlen(environ[j]));
		j++;
	}
	while (environ[j] && ft_strcmp(search, "HOME"))
	{
		if (!ft_strncmp(environ[j], search, ft_strlen(search))
			&& environ[j][ft_strlen(search)] == '=')
			ret = ft_strsub(environ[j], ft_strlen(search) + 1,
					ft_strlen(environ[j]));
		j++;
	}
	return (ret);
}

static void	replace_environ(char **av, char **environ, char *str,
		t_norme *norme)
{
	char	*search;
	char	*cat;
	char	*ret;
	char	*tmp;
	char	*tmp2;

	ret = ft_strdup(av[norme->i]);
	cat = NULL;
	tmp = NULL;
	tmp2 = NULL;
	if ((ft_strlen(ret) > 0) && !ft_strcmp(str, "HOME"))
		cat = ft_strsub(ret, 1, ft_strlen(ret));
	if (!ft_strcmp(str, "HOME"))
		search = ft_strdup(str);
	else
		search = parse_search(ret);
	tmp = replace_environ_suite(environ, search);
	if (tmp && cat)
		tmp2 = ft_strjoin(tmp, cat);
	if (tmp2)
		replace_envrion_suite_2(tmp2, search, norme, av);
	else
		replace_envrion_suite_2(tmp, search, norme, av);
	free_elements(cat, search, ret, tmp);
	ft_memdel((void**)&tmp2);
}

void		check_tilde_and_dollar(char **environ, char **av, int boolean)
{
	t_norme	*norme;

	norme = (t_norme*)ft_memalloc(sizeof(t_norme));
	norme->i = 0;
	norme->boolean = boolean;
	while (av[norme->i])
	{
		if (!ft_strcmp(av[norme->i], "$"))
			return ;
		if (av[norme->i][0] == '~')
			replace_environ(av, environ, "HOME", norme);
		else if (av[norme->i][0] == '$')
			replace_environ(av, environ, "$", norme);
		norme->i++;
	}
	free_struct(norme);
}
