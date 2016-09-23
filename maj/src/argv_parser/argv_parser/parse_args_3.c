/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 11:47:11 by fjacquem          #+#    #+#             */
/*   Updated: 2016/09/22 11:47:14 by fjacquem         ###   ########.fr       */
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
	int		dquote;

	dquote = 0;
	i = 0;
	while ((*av)[i])
	{
		if ((*av)[i] == '\'' && !dquote)
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
		else if ((*av)[i] == '"')
			dquote = 1;
		i++;
	}
}
