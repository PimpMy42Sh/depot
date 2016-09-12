/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 17:39:24 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/12 16:46:44 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

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
