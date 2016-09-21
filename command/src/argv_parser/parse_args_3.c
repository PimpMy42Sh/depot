/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 17:39:24 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/21 19:43:31 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_token(char *s)
{
	char	*tmp;
	char	*ret;
	int		len;

	len = 0;
	tmp = s;
	while (*s && ft_isalnum(*s))
	{
		len++;
		s++;
	}
	ret = ft_strnew(len);
	ft_strncpy(ret, tmp, len);
	return (ret);
}

void	check_tilde_and_dollar__str(char **environ, char **av)
{
	int		i;

	i = 0;
	while ((*av)[i])
	{
		if ((*av)[i] == '\'')
		{
			i++;
			while ((*av)[i] != '\'')
				i++;
		}
		else if ((*av)[i] == '~')
		{
			if ((*av)[i + 1] != '~')
				replace_tilde(av, &i, environ);
			else
				while ((*av)[i + 1] == '~')
					i++;
		}
		else if ((*av)[i] == '$')
			replace_dollar(av, &i, environ);
		i++;
	}
}
