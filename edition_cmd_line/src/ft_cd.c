/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/23 19:00:18 by mfamilar          #+#    #+#             */
/*   Updated: 2016/05/10 16:44:16 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		cd_too_many_args(void)
{
	ft_putstr_fd("cd: Too many arguments.\n", 2);
	return (1);
}

static int		move_to_env_suite(char **environ, char *cat,
		char *pwd, char *oldpwd)
{
	char	*tmp;

	tmp = NULL;
	if (cat)
	{
		tmp = ft_strjoin(pwd, cat);
		pwd = ft_strdup(tmp);
		ft_memdel((void**)&tmp);
	}
	if (pwd && chdir(pwd) == 0)
	{
		move_old_and_pwd(environ, oldpwd, pwd);
		free_elements(NULL, cat, pwd, NULL);
		return (0);
	}
	else
	{
		cant_move_home();
		free_elements(pwd, cat, NULL, NULL);
		return (1);
	}
}

static int		move_to_env(char **environ, char *env, char *av)
{
	char	*oldpwd;
	char	*pwd;
	char	buffer[256];
	char	*cat;
	char	*tmp;

	cat = NULL;
	tmp = NULL;
	if (!ft_strcmp(env, "OLDPWD") && ft_strlen(av) > 0)
	{
		tmp = ft_strsub(av, 1, ft_strlen(av));
		cat = ft_strdup(tmp);
		av = ft_strdup(tmp);
	}
	oldpwd = getcwd(buffer, 256);
	pwd = return_env(environ, env);
	if (!pwd)
	{
		cant_move_home();
		move_old_and_pwd(environ, oldpwd, pwd);
		free_elements(pwd, cat, tmp, NULL);
		return (1);
	}
	ft_memdel((void**)&tmp);
	return (move_to_env_suite(environ, cat, pwd, oldpwd));
}

static int		move_to_dir(char **environ, char *path)
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
		move_old_and_pwd(environ, oldpwd, pwd);
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

int				ft_cd(char **av, char **environ)
{
	int		i;

	i = 0;
	ft_putchar('\n');
	while (av[i])
		i++;
	if (i >= 3)
		return (cd_too_many_args());
	if (!av[1] || (av[1] && !ft_strcmp(av[1], "--")))
		return (move_to_env(environ, "HOME", av[1]));
	if (av[1][0] == '-')
		return (move_to_env(environ, "OLDPWD", av[1]));
	else
		move_to_dir(environ, av[1]);
	return (0);
}
