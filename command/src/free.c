/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/18 18:06:41 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/21 19:50:47 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
