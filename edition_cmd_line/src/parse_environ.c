/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_environ.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/25 12:31:24 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/17 17:52:46 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		move_old_and_pwd_suite(t_norme *norme, char **environ,
		char *old)
{
	char	*ret;
	char	buffer[256];

	ret = NULL;
	if (return_env_indice(environ, "PWD"))
		norme->current = 0;
	if (norme->current || norme->previous)
	{
		if (old && norme->previous)
		{
			ft_memdel((void**)&environ[norme->i]);
			environ[norme->i] = ft_strjoin("OLDPWD=", old);
			norme->i++;
		}
		if (norme->current)
		{
			ret = getcwd(buffer, 256);
			if (!ret)
				permission_denied("cd", "");
			else
			{
				ft_memdel((void**)&environ[norme->i]);
				environ[norme->i] = ft_strjoin("PWD=", ret);
			}
		}
	}
}

void			move_old_and_pwd(char **environ, char *old, char *pwd)
{
	t_norme	*norme;
	char	*tmp;
	char	*tmp2;

	tmp = NULL;
	tmp2 = NULL;
	norme = ft_memalloc(sizeof(t_norme));
	norme->i = 0;
	norme->current = 1;
	norme->previous = 1;
	while (environ[norme->i])
	{
		if (old && !ft_strncmp(environ[norme->i], "OLDPWD", 6))
		{
			ft_strclr(environ[norme->i]);
			environ[norme->i] = ft_strjoin("OLDPWD=", old);
			norme->previous = 0;
		}
		if (pwd && !ft_strncmp(environ[norme->i], "PWD", 3))
		{
			ft_strclr(environ[norme->i]);
			environ[norme->i] = ft_strjoin("PWD=", pwd);
			norme->current = 0;
		}
		norme->i++;
	}
	move_old_and_pwd_suite(norme, environ, old);
	free_struct(norme);
}

char			*return_env(char **environ, char *env)
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

int				return_env_indice(char **environ, char *env)
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

void			remove_env(char **av, int indice)
{
	while (av[indice])
	{
		av[indice] = av[indice + 1];
		indice++;
	}
}
