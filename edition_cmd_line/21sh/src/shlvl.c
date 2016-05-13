/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 16:49:49 by mfamilar          #+#    #+#             */
/*   Updated: 2016/04/28 11:10:51 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		incremente_shlvl(char **environ, int i, char *lvl)
{
	int		intlvl;
	char	*tmp;

	intlvl = 0;
	tmp = NULL;
	intlvl = ft_atoi(lvl);
	if (intlvl)
		intlvl++;
	else
		intlvl = 1;
	lvl = ft_itoa(intlvl);
	tmp = ft_strdup(environ[i]);
	tmp[6] = 0;
	environ[i] = ft_strjoin(tmp, lvl);
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&lvl);
}

static void		create_shlvl(char **environ)
{
	int			i;

	if (!environ[0])
		i = 0;
	else
		i = return_env_size(environ);
	environ[i] = ft_strdup("SHLVL=1");
	environ[i + 1] = 0;
}

void			check_shlvl(char **environ)
{
	int		i;
	char	*charlvl;

	i = 0;
	charlvl = NULL;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], "SHLVL", 5))
		{
			charlvl = ft_strsub(environ[i], 6, ft_strlen(environ[i]));
			if (charlvl)
				incremente_shlvl(environ, i, charlvl);
			else
				return ;
			ft_memdel((void**)&charlvl);
			return ;
		}
		i++;
	}
	create_shlvl(environ);
}
