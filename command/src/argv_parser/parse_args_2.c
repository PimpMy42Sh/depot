/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 17:42:35 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/12 16:47:13 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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

/*
** Si le boolean est égale à 1, et que l'on essaye d'accéder à une variable
** d'environnement qui n'éxiste pas (ex $FAKE), le programme affiche
** "undefined_variable" sur la sortie d'erreur et exit(1). Il faut donc être
** dans un processus fils car sinon le shell quitte.
** Si le boolean est 0, alors le programme affichera $FAKE car il n'aura pas
** trouvé de correspondance dans l'environnement. Il n'éxit pas et peut donc
** être appelé en dehors d'un fork().
*/

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
