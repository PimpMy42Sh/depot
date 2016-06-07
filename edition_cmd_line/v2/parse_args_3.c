/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 17:39:24 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/10 10:27:42 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_builtins(char **av, t_env *env)
{
	int		i;

	i = 1;
	if (av[0] && !ft_strcmp(av[0], "exit"))
		ft_exit(av, env);
	if (av[0] && !ft_strcmp(av[0], "cd"))
		ft_cd(av, env);
	if (av[0] && !ft_strcmp(av[0], "setenv"))
		ft_setenv(av, env);
	if (av[0] && !ft_strcmp(av[0], "unsetenv"))
		ft_unsetenv(av, env);
	if (!ft_strcmp(av[0], "env"))
	{
		i = ft_env(av, env->environ);
		resumed_terminal();
	}
	free_double_array(av);
	return (i);
}

void	replace_envrion_suite_2(char *ret, char *search, t_norme *norme,
		char **av)
{
	if (!ret && norme->boolean)
		undefined_variable(search);
	if (ret)
	{
		ft_memdel((void**)&av[norme->i]);
		av[norme->i] = ft_strdup(ret);
	}
}

char	*parse_search(char *ret)
{
	char	*tmp;

	tmp = ft_strsub(ret, 1, ft_strlen(ret));
	return (tmp);
}

int		return_av_size(char **av)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (av[i])
	{
		j += ft_strlen(av[i]);
		i++;
	}
	return (j + 1);
}
