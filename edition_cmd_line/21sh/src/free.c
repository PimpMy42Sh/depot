/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Marco <Marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 18:06:41 by mfamilar          #+#    #+#             */
/*   Updated: 2016/04/28 18:27:00 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		free_env(char *path, char **path_env)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	ft_memdel((void**)&path);
	while (path_env[i])
	{
		ft_memdel((void**)&path_env[i]);
		i++;
	}
	ft_memdel((void**)&path_env);
}

void		free_double_array(char **arr)
{
	int		i;

	i = 0;
	while (arr[i] != NULL)
	{
		ft_memdel((void**)&arr[i]);
		i++;
	}
	ft_memdel((void**)&arr);
}

void		free_elements(char *one, char *two, char *three, char *four)
{
	ft_memdel((void**)&one);
	ft_memdel((void**)&two);
	ft_memdel((void**)&three);
	ft_memdel((void**)&four);
}

void		free_struct(t_norme *s)
{
	ft_memdel((void**)&s->old);
	ft_memdel((void**)&s->pwd);
	ft_memdel((void**)&s->str);
	if (s->copy)
		free_double_array(s->copy);
	ft_memdel((void**)&s);
}

void		free_cmd(char **cmd)
{
	int			i;

	i = 0;
	while (cmd[i])
	{
		ft_memdel((void**)&cmd[i]);
		i++;
	}
	ft_memdel((void**)&cmd);
}
