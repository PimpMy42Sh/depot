/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsetenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/04 14:24:01 by mfamilar          #+#    #+#             */
/*   Updated: 2016/04/26 10:46:03 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_unsetenv(char **av, char **environ)
{
	int		i;

	i = return_env_size(av);
	if (i == 1)
	{
		unsetenv_error();
		return ;
	}
	else
		loop_remove_env(av, environ);
	ft_putchar('\n');
}
