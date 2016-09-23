/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 11:48:43 by fjacquem          #+#    #+#             */
/*   Updated: 2016/09/22 11:48:47 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"
#include "../../include/minishell.h"
#include <command.h>

static void		cd_too_many_args(void)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("cd: Too many arguments.\n", 2);
	ft_putstr_fd(RESET, 2);
}

static void		move_to_dir(t_env *env, char *path)
{
	char	*oldpwd;
	char	*pwd;
	char	buffer[256];

	pwd = getcwd(buffer, 256);
	if (pwd)
		oldpwd = ft_strdup(pwd);
	else
	{
		oldpwd = return_env(env->environ, "PWD");
		if (!oldpwd)
			oldpwd = ft_strdup(".");
	}
	if (chdir(path) == -1)
	{
		if (!ft_strcmp(path, ".") || !ft_strcmp(path, ".."))
			permission_denied("cd", path);
		else if (!test_access(path))
			no_such_file(path);
		free_elements(oldpwd, path, 0, 0);
		return ;
	}
	pwd = getcwd(buffer, 256);
	move_old_and_pwd(env, oldpwd, pwd);
	free_elements(oldpwd, path, 0, 0);
}

static void		move_to_env(t_env *environ, int home)
{
	char		*path;

	if (home)
		path = return_env(environ->environ, "HOME");
	else
		path = return_env(environ->environ, "OLDPWD");
	if (!path)
	{
		if (home)
			cant_move_home();
		else
		{
			ft_putstr_fd(RED, 2);
			ft_putstr_fd("cd: OLDPWD not set", 2);
			ft_putstr_fd(RESET, 2);
		}
		return ;
	}
	else
		move_to_dir(environ, path);
}

void			ft_cd(char **av, t_env *env)
{
	char	*path;
	int		i;

	i = 0;
	path = NULL;
	while (av[i])
		i++;
	if (i >= 3)
		cd_too_many_args();
	else if (!av[1] || (av[1] && !ft_strcmp(av[1], "--")))
		move_to_env(env, 1);
	else if (av[1][0] == '-')
		move_to_env(env, 0);
	else
	{
		path = ft_strdup(av[1]);
		move_to_dir(env, path);
	}
}