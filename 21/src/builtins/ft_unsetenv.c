/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 14:24:01 by mfamilar          #+#    #+#             */
/*   Updated: 2016/08/23 17:05:37 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void		ft_unsetenv(char **av, t_env *env)
{
	int		i;

	i = return_env_size(av);
	if (i == 1)
	{
		unsetenv_error();
		return ;
	}
	else
		loop_remove_env(av, env);
}
