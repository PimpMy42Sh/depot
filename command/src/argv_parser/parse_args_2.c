/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_args_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/29 17:42:35 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/21 19:40:41 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*ft_strtrim_quotes(char *s)
{
	char	*ref;
	char	*ret;

	ref = s;
	ret = ref;
	while (*s)
	{
		if (*s != '\'' && *s != '\"')
			*(ref++) = *(s++);
		else
			s++;
	}
	*ref = 0;
	return (ret);
}

void		replace_tilde(char **origin, int *index, char **environ)
{
	char	*ret;
	char	*var;
	int		var_len;

	if (!(var = return_env(environ, "HOME")))
		var = "\0";
	var_len = ft_strlen(var);
	ret = ft_strnew(var_len + ft_strlen(*origin));
	*((*origin) + (*index)) = 0;
	ft_strcpy(ret, *origin);
	ft_strcpy(ret + (*index), var);
	ft_strcpy(ret + (*index) + var_len, *origin + (*index) + 1);
	free(*origin);
	*index += var_len - 1;
	*origin = ret;
	if (var_len)
		free(var);
}

static void		replace_environ(char **origin, int *index,
			char **environ, char *str)
{
	char	*ret;
	char	*var;
	int		var_len;

	if (!(var = return_env(environ, str)))
		var = "\0";
	var_len = ft_strlen(var);
	ret = ft_strnew(var_len + ft_strlen(*origin));
	*((*origin) + (*index)) = 0;
	ft_strcpy(ret, *origin);
	ft_strcpy(ret + (*index), var);
	ft_strcpy(ret + (*index) + var_len,
		*origin + (*index) + ft_strlen(str) + 1);
	free(*origin);
	*index += var_len - 1;
	*origin = ret;
	if (var_len)
		free(var);
}

void		replace_dollar(char **av, int *i, char **environ)
{
	char	*token;

	token = get_token(&(*av)[(*i) + 1]);
	replace_environ(av, i, environ, token);
	free(token);
}

void		check_tilde_and_dollar(char **environ, char **av)
{
	int		i;

	i = 0;
	while (av[i])
	{
		check_tilde_and_dollar__str(environ, &av[i]);
		ft_strtrim_quotes(av[i]);
		i++;
	}
}
