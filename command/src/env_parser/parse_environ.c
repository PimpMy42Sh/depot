/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_environ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 12:31:24 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/21 19:12:21 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	move_old_and_pwd_suite(t_norme *norme, t_env *env,
		char *old)
{
	char	*ret;
	char	buffer[256];

	if (return_env_indice(env->environ, "PWD") != -1)
		norme->current = 0;
	if (norme->current || norme->previous)
	{
		if (old && norme->previous)
		{
			ft_memdel((void**)&env->environ[norme->i]);
			append_item_environ(env, "OLDPWD", old);
			norme->i++;
		}
		if (norme->current)
		{
			ret = getcwd(buffer, 256);
			if (!ret)
				permission_denied("cd", "");
			else
			{
				ft_memdel((void**)&env->environ[norme->i]);
				append_item_environ(env, "PWD", ret);
			}
		}
	}
}

void		move_old_and_pwd(t_env *env, char *old, char *pwd)
{
	t_norme	*norme;

	norme = (t_norme*)ft_memalloc(sizeof(t_norme));
	ft_bzero(norme, sizeof(t_norme));
	norme->current = 1;
	norme->previous = 1;
	while (env->environ[norme->i])
	{
		if (old && !ft_strncmp(env->environ[norme->i], "OLDPWD", 6))
		{
			ft_memdel((void**)&env->environ[norme->i]);
			env->environ[norme->i] = ft_strjoin("OLDPWD=", old);
			norme->previous = 0;
		}
		if (pwd && !ft_strncmp(env->environ[norme->i], "PWD", 3))
		{
			ft_memdel((void**)&env->environ[norme->i]);
			env->environ[norme->i] = ft_strjoin("PWD=", pwd);
			norme->current = 0;
		}
		norme->i++;
	}
	move_old_and_pwd_suite(norme, env, old);
	free_struct(norme);
}

char		*return_env(char **environ, char *env)
{
	int		i;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], env, ft_strlen(env)))
			return (ft_strsub(environ[i], ft_strlen(env) + 1,
						ft_strlen(environ[i])));
			i++;
	}
	return (NULL);
}

int			return_env_indice(char **environ, char *env)
{
	int		i;

	i = 0;
	while (environ[i])
	{
		if (!ft_strncmp(environ[i], env, ft_strlen(env))
				&& environ[i][ft_strlen(env)] == '=')
			return (i);
		i++;
	}
	return (-1);
}

void		remove_env(char **av, int indice)
{
	char		*tmp;

	tmp = av[indice];
	while (av[indice])
	{
		av[indice] = av[indice + 1];
		indice++;
	}
	ft_memdel((void**)&tmp);
}
