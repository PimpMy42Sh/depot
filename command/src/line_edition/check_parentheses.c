/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parentheses.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Marco <Marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 17:29:23 by Marco             #+#    #+#             */
/*   Updated: 2016/08/25 17:30:40 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	check_close_par(char *line, char open, char close, int i)
{
	int		open_counter;
	int		close_counter;

	open_counter = 0;
	close_counter = 0;
	while (line[i])
	{
		if (line[i] == close)
			close_counter++;
		else if (line[i] == open)
			open_counter++;
		i++;
	}
	if (open_counter > close_counter)
		return (1);
	else
		return (0);
}

int	check_parentheses(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == PARENTHESES)
		{
			if (check_close_par(line, PARENTHESES, C_PARENTHESES, i))
					return (BAD_PARENTHESE);
		}
		else if (line[i] == ACCOLADES)
		{
			if (check_close_par(line, ACCOLADES, C_ACCOLADES, i))
				return (BAD_ACCOLADES);
		}
		else if (line[i] == CROCHETS)
		{
			if (check_close_par(line, CROCHETS, C_CROCHETS, i))
				return (BAD_CROCHETS);
		}
	}
	return (0);
}
