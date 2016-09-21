/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shlvl.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/21 16:49:49 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/21 18:14:52 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void		incremente_shlvl(t_env *env, int i, char *lvl)
{
	int		intlvl;
	char	*tmp;

	tmp = NULL;
	intlvl = ft_atoi(lvl);
	if (intlvl)
		intlvl++;
	else
		intlvl = 1;
	lvl = ft_itoa(intlvl);
	tmp = ft_strdup(env->environ[i]);
	tmp[6] = 0;
	ft_memdel((void**)&env->environ[i]);
	env->environ[i] = ft_strjoin(tmp, lvl);
	ft_memdel((void**)&tmp);
	ft_memdel((void**)&lvl);
}

void			check_shlvl(t_env *env)
{
	int		i;
	char	*charlvl;

	charlvl = NULL;
	i = 0;
	while (env->environ[i])
	{
		if (!ft_strncmp(env->environ[i], "SHLVL", 5))
		{
			charlvl = ft_strsub(env->environ[i], 6, ft_strlen(env->environ[i]));
			if (charlvl)
				incremente_shlvl(env, i, charlvl);
			else
				return ;
			ft_memdel((void**)&charlvl);
			return ;
		}
		i++;
	}
	append_item_environ(env, "SHLVL", "1");
}
