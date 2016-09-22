/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_synthax_and_close.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfamilar <mfamilar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/12 15:25:19 by mfamilar          #+#    #+#             */
/*   Updated: 2016/09/22 12:53:26 by mfamilar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int		check_synthax(char *s)
{
	int		compteur[3];
	int		i;

	i = 0;
	ft_bzero(compteur, sizeof(compteur));
	while (s[i])
	{
		if (s[i] == PARENTHESES)
			compteur[0]++;
		else if (s[i] == ACCOLADES)
			compteur[1]++;
		else if (s[i] == CROCHETS)
			compteur[2]++;
		if (s[i] == C_PARENTHESES)
			compteur[0]--;
		else if (s[i] == C_ACCOLADES)
			compteur[1]--;
		else if (s[i] == C_CROCHETS)
			compteur[2]--;
		if (compteur[0] < 0 || compteur[1] < 0 || compteur[2] < 0)
			return (SYNTAX_ERROR);
		i++;
	}
	return (0);
}

static char		verif_tmp(char tmp)
{
	if (tmp == QUOTES || tmp == D_QUOTES || tmp == B_QUOTES)
		return (tmp);
	if (tmp == PARENTHESES)
		return (C_PARENTHESES);
	if (tmp == ACCOLADES)
		return (C_ACCOLADES);
	if (tmp == CROCHETS)
		return (C_CROCHETS);
	return (0);
}

static char		skip_quote(char **s, char tmp)
{
	char		end;

	end = verif_tmp(tmp);
	while (**s && **s != end)
		(*s)++;
	return (end);
}

static int		check_line_is_close(char **s, char **back)
{
	char	tmp;
	char	end;
	char	*begin;

	begin = ft_strdup(*s);
	while (**s)
	{
		if (**s == QUOTES || **s == D_QUOTES || **s == B_QUOTES ||
			**s == PARENTHESES || **s == ACCOLADES || **s == CROCHETS)
		{
			tmp = **s;
			(*s)++;
			end = skip_quote(s, tmp);
			if (!**s)
				if (quote_not_close(begin, &end, back))
				{
					ft_memdel((void**)&begin);
					return (1);
				}
		}
		(*s)++;
	}
	ft_memdel((void*)&begin);
	return (0);
}

int				check_line_quotes(char *s, char **back)
{
	if (check_synthax(s))
	{
		ft_putstr_fd(RED, 2);
		ft_putstr_fd("syntax error", 2);
		ft_putstr_fd(RESET, 2);
		return (1);
	}
	else
	{
		if (check_line_is_close(&s, back))
			return (1);
	}
	return (0);
}
