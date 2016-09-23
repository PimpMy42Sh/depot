/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 11:50:18 by fjacquem          #+#    #+#             */
/*   Updated: 2016/09/22 11:50:20 by fjacquem         ###   ########.fr       */
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
