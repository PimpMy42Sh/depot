/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_close.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Marco <Marco@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/08/25 17:24:41 by Marco             #+#    #+#             */
/*   Updated: 2016/08/25 17:28:11 by Marco            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	    check_close_quotes(char *line, char close)
{
	int		i;
	int		count;

	count = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == close)
			count++;
		i++;
	}
	return (count % 2 == 0 ? 0 : 1);
}

static int			check_quotes(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == QUOTES)
		{
			if (check_close_quotes(line, QUOTES))
				return (BAD_QUOTES);
		}
		else if (line[i] == D_QUOTES)
		{
			if (check_close_quotes(line, D_QUOTES))
				return (BAD_D_QUOTES);
			i++;
			while (line[i] != D_QUOTES && line[i])
				i++;
		}
		else if (line[i] == B_QUOTES)
		{
			if (check_close_quotes(line, B_QUOTES))
				return (BAD_B_QUOTES);
		}
	}
	return (0);
}

static int	   check_syntax(char *line, char open, char close, int i)
{
	int		open_counter;
	int		close_counter;

	open_counter = 0;
	close_counter = 0;
	while (i)
	{
		if (line[i] == close)
			close_counter++;
		else if (line[i] == open)
			open_counter++;
		i--;
	}
	if (open_counter < close_counter)
		return (1);
	else
		return (0);
}

static int	   check_syntax_error(char *line)
{
	int		i;

	i = -1;
	while (line[++i])
	{
		if (line[i] == C_PARENTHESES)
		{
			if (check_syntax(line, PARENTHESES, C_PARENTHESES, i))
				return (SYNTAX_ERROR);
		}
		else if (line[i] == C_ACCOLADES)
		{
			if (check_syntax(line, ACCOLADES, C_ACCOLADES, i))
				return (SYNTAX_ERROR);
		}
		else if (line[i] == C_CROCHETS)
		{
			if (check_syntax(line, CROCHETS, C_CROCHETS, i))
				return (SYNTAX_ERROR);
		}
	}
	return (0);
}

int			      check_line_is_close(char **line)
{
	int			i;

	if ((i = check_syntax_error(*line)))
		return (i);
	else if ((i = check_quotes(line)))
		return (i);
	else
		return (i = check_parentheses(line));
}
