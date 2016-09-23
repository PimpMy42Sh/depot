/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   identification.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjacquem <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/22 11:52:49 by fjacquem          #+#    #+#             */
/*   Updated: 2016/09/22 11:52:51 by fjacquem         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <command.h>

/*
**	Le symbole actuel est'il une redirection (ou argregateur) ?
**
**	s:	chaine a verifier
*/

int						is_a_redirection(char *cmd)
{
	while (ft_isdigit(*cmd))
		cmd++;
	return (*cmd == '>' || *cmd == '<');
}

/*
**	Le symbole actuel est'il un caractere speciale ?
**
**	c:	caractere verifier
*/

int						is_a_spec_char(int c)
{
	return (c == '|' || c == '<' || c == '>' || c == ';');
}
