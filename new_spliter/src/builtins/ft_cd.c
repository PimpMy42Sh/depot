/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 19:00:18 by mfamilar          #+#    #+#             */
/*   Updated: 2016/07/22 10:39:38 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int		cd_too_many_args(void)
{
	ft_putstr_fd("cd: Too many arguments.\n", 2);
	return (1);
}

static int		move_to_env_suite(t_env *env, char *cat,
		char *pwd, char *oldpwd)
{
	char	*tmp;

	tmp = NULL;
	if (cat)
	{
		tmp = pwd;
		pwd = ft_strjoin(pwd, cat);
		ft_memdel((void**)&tmp);
	}
	if (pwd && chdir(pwd) == 0)
	{
		move_old_and_pwd(env, oldpwd, pwd);
		free_elements(pwd, cat, NULL, NULL);
		return (0);
	}
	else
	{
		cant_move_home();
		free_elements(pwd, cat, NULL, NULL);
		return (1);
	}
}

static int		move_to_env(t_env *environ, char *env, char *av, char *oldpwd)
{
	char	*pwd;
	char	buffer[256];
	char	*cat;
	char	*tmp;

	cat = NULL;
	tmp = NULL;
	pwd = NULL;
	if (!ft_strcmp(env, "OLDPWD") && ft_strlen(av) > 0)
	{
		tmp = ft_strsub(av, 1, ft_strlen(av));
		cat = ft_strdup(tmp);
		av = ft_strdup(tmp);
	}
	oldpwd = getcwd(buffer, 256);
	pwd = return_env(environ->environ, env);
	if (!pwd)
	{
		cant_move_home();
		move_old_and_pwd(environ, oldpwd, pwd);
		free_elements(pwd, cat, tmp, av);
		return (1);
	}
	free_elements(tmp, av, NULL, NULL);
	return (move_to_env_suite(environ, cat, pwd, oldpwd));
}

static int		move_to_dir(t_env *env, char *path)
{
	char	*oldpwd;
	char	*pwd;
	char	buffer[256];

	pwd = getcwd(buffer, 256);
	if (!pwd)
	{
		permission_denied("cd", path);
		return (1);
	}
	oldpwd = ft_strdup(pwd);
	if (chdir(path) == 0)
	{
		pwd = getcwd(buffer, 256);
		move_old_and_pwd(env, oldpwd, pwd);
		ft_memdel((void**)&oldpwd);
		return (0);
	}
	else
	{
		no_such_file(path);
		ft_memdel((void**)&oldpwd);
		return (-1);
	}
}

int			ft_cd(char **av, t_env *env)
{
	int		i;
	char	*oldpwd;

	oldpwd = NULL;
	i = 0;
	ft_putchar('\n');
	while (av[i])
		i++;
	if (i >= 3)
		return (cd_too_many_args());
	if (!av[1] || (av[1] && !ft_strcmp(av[1], "--")))
		return (move_to_env(env, "HOME", av[1], oldpwd));
	if (av[1][0] == '-')
		return (move_to_env(env, "OLDPWD", av[1], oldpwd));
	else
		move_to_dir(env, av[1]);
	return (0);
}
